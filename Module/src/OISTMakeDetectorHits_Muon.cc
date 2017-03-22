#include "OISTMakeDetectorHits_Muon.hh"
#include <iostream>
#include <boost/format.hpp>
#include "FlagDefinition.hh"


using namespace anl;
using namespace comptonsoft;


namespace {

typedef std::list<comptonsoft::DetectorHit_sptr> HitList;

bool is_group_adjacent(const HitList& group0, const HitList& group1) {
  for (const auto& hit0: group0) {
    for (const auto& hit1: group1) {
      if (hit0->isAdjacent(*hit1, true)) {
        return true;
      }
    }
  }
  return false;
}

} /* anonymous namespace */


namespace oistapp
{

  ANLStatus OISTMakeDetectorHits_Muon::mod_startup()
  {
    
    register_parameter(&m_AnalysisMode, "analysis_mode");
    register_parameter(&m_Esearch_Ld, "energy_window_ld", keV, "keV");
    register_parameter(&m_Esearch_Ud, "energy_window_ud", keV, "keV");
    
    SelectHits::mod_startup();    
  }

  ANLStatus OISTMakeDetectorHits_Muon::mod_his()
  {
    GetANLModule("OISTReadDataFile", &readDatafile_);
    VCSModule::mod_his();
    mkdir();
    
    DetectorSystem* detectorManager = getDetectorManager();
    
    for(int i=0;i<(detectorManager->NumberOfDetectors());i++){
      VRealDetectorUnit* detunit = detectorManager->getDetectorByIndex(i);
      int detid = detunit->getID();
      int pixelx = detunit->getNumPixelX();
      int pixely = detunit->getNumPixelY();
      
      TH2F *hist_org = 0;
      std::string name = (boost::format("multiplicity_org_%04d") % detid).str();
      hist_org = new TH2F(name.c_str(), "multiplicity_org", pixelx, -0.5, pixelx-0.5, pixely, -0.5, pixely-0.5);
      hist_org->GetXaxis()->SetTitle("Multiplicity(Anode)");
      hist_org->GetYaxis()->SetTitle("Multiplicity(Cathode)");
      m_Multiplicity_org[detid] = hist_org;

      TH2F *hist_clustered = 0;
      name = (boost::format("multiplicity_clustered_%04d") % detid).str();
      hist_clustered = new TH2F(name.c_str(), "multiplicity_clustered", pixelx, -0.5, pixelx-0.5, pixely, -0.5, pixely-0.5);
      hist_clustered->GetXaxis()->SetTitle("Multiplicity(Anode)");
      hist_clustered->GetYaxis()->SetTitle("Multiplicity(Cathode)");
      m_Multiplicity_clustered[detid] = hist_clustered;

      TH2D *hist_image = 0;
      name = (boost::format("tmp_detectorimage_%04d") % detid).str();
      hist_image = new TH2D(name.c_str(), "tmp_detectorimage", pixelx, -0.5, pixelx-0.5, pixely, -0.5, pixely-0.5);
      hist_image->GetXaxis()->SetTitle("Anode Strip");
      hist_image->GetYaxis()->SetTitle("Cathode Strip");
      tmp_detectorimage[detid] = hist_image;
      
      TH2D *hist_image_clustered = 0;
      name = (boost::format("tmp_detectorimage_clustered_%04d") % detid).str();
      hist_image_clustered = new TH2D(name.c_str(), "tmp_detectorimage_clustered", pixelx, -0.5, pixelx-0.5, pixely, -0.5, pixely-0.5);
      hist_image_clustered->GetXaxis()->SetTitle("Anode Strip");
      hist_image_clustered->GetYaxis()->SetTitle("Cathode Strip");
      tmp_detectorimage_clustered[detid] = hist_image_clustered;
      
      TH2D *hist_image_timecut = 0;
      name = (boost::format("tmp_detectorimage_timecut_%04d") % detid).str();
      hist_image_timecut = new TH2D(name.c_str(), "tmp_detectorimage_timecut", pixelx, -0.5, pixelx-0.5, pixely, -0.5, pixely-0.5);
      hist_image_timecut->GetXaxis()->SetTitle("Anode Strip");
      hist_image_timecut->GetYaxis()->SetTitle("Cathode Strip");
      tmp_detectorimage_timecut[detid] = hist_image_timecut;
      
      TH2D *hist_image_clustered_timecut = 0;
      name = (boost::format("tmp_detectorimage_clustered_timecut_%04d") % detid).str();
      hist_image_clustered_timecut = new TH2D(name.c_str(), "tmp_detectorimage_clustered_timecut", pixelx, -0.5, pixelx-0.5, pixely, -0.5, pixely-0.5);
      hist_image_clustered_timecut->GetXaxis()->SetTitle("Anode Strip");
      hist_image_clustered_timecut->GetYaxis()->SetTitle("Cathode Strip");
      tmp_detectorimage_clustered_timecut[detid] = hist_image_clustered_timecut;

      TH2D *hist_image_clustered_timecut_multiplicity = 0;
      name = (boost::format("tmp_multiplicity_clustered_timecut_%04d") % detid).str();
      hist_image_clustered_timecut_multiplicity = new TH2D(name.c_str(), "tmp_multiplicity_clustered_timecut", pixelx, -0.5, pixelx-0.5, pixely, -0.5, pixely-0.5);
      hist_image_clustered_timecut_multiplicity->GetXaxis()->SetTitle("Anode Strip");
      hist_image_clustered_timecut_multiplicity->GetYaxis()->SetTitle("Cathode Strip");
      tmp_multiplicity_clustered_timecut[detid] = hist_image_clustered_timecut_multiplicity;


      TH2D *hist_image_clustered_multiplicity = 0;
      name = (boost::format("tmp_multiplicity_clustered_%04d") % detid).str();
      hist_image_clustered_multiplicity = new TH2D(name.c_str(), "tmp_multiplicity_clustered", pixelx, -0.5, pixelx-0.5, pixely, -0.5, pixely-0.5);
      hist_image_clustered_multiplicity->GetXaxis()->SetTitle("Anode Strip");
      hist_image_clustered_multiplicity->GetYaxis()->SetTitle("Cathode Strip");
      tmp_multiplicity_clustered[detid] = hist_image_clustered_multiplicity;

      
    }
    return AS_OK;
  }
  
  
  void OISTMakeDetectorHits_Muon::doProcessing()
  {
    //    std::cout<< "OISTMakeDetectorHits_Muon::doProcessing()" << std::endl;
    
    
    
    DetectorSystem* detectorManager = getDetectorManager();
    for (auto& detector: detectorManager->getDetectors()) {
      
      RealDetectorUnit2DStrip* dsd = dynamic_cast<RealDetectorUnit2DStrip*>(detector.get());
      cathodeSideHits_.clear();
      anodeSideHits_.clear();
      reconstructedHits_.clear();
      
      int detid = detector->getID();      
      detector->selectHits();
      const int numhit = detector->NumberOfDetectorHits();
      for(int i=0;i<numhit;i++){
	DetectorHit_sptr hit = detector->getDetectorHit(i);
	if(hit->isFlags(flag::AnodeSide)){
	  anodeSideHits_.push_back(hit->clone());
	}else if(hit->isFlags(flag::CathodeSide)){
	  cathodeSideHits_.push_back(hit->clone());
	}else{
	  std::cout << "undefined ..." << std::endl; 
	}
	
      }
      comptonsoft::DetectorHitVector org_anodeSideHits_ = anodeSideHits_;
      comptonsoft::DetectorHitVector org_cathodeSideHits_ = cathodeSideHits_;
      
      m_Multiplicity_org[detid]->Fill(anodeSideHits_.size(),cathodeSideHits_.size());
      
      unsigned long int exptime = readDatafile_->getExpTime();
      int anodecandidate_org = 0;
      int anodestrip_org = 0;
      int cathodecandidate_org = 0;
      int cathodestrip_org = 0;
      
      for(int i=0;i<anodeSideHits_.size();i++){
	double energy  = anodeSideHits_[i]->EPI();
	if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	  anodecandidate_org += 1;
	  anodestrip_org = anodeSideHits_[i]->PixelY();
	}
      }
      for(int j=0;j<cathodeSideHits_.size();j++){
	double energy  = cathodeSideHits_[j]->EPI();
	if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	  cathodecandidate_org += 1;
	  cathodestrip_org = cathodeSideHits_[j]->PixelX();
	}
      }
      if(anodecandidate_org == 1 && cathodecandidate_org==1){
	tmp_detectorimage[detid]->Fill(anodestrip_org,cathodestrip_org);
	if(1088<=exptime && exptime < 1098) tmp_detectorimage_timecut[detid]->Fill(anodestrip_org,cathodestrip_org);
      }
      
      auto compairStrip = [](const DetectorHit_sptr& h1, const DetectorHit_sptr& h2)-> bool {
	return ((h1->isXStrip() && (h1->Pixel().X() < h2->Pixel().X()))
		|| (h1->isYStrip() && (h1->Pixel().Y() < h2->Pixel().Y())));
      };
      
      std::sort(anodeSideHits_.begin(), anodeSideHits_.end(), compairStrip);
      std::sort(cathodeSideHits_.begin(), cathodeSideHits_.end(), compairStrip);
      
      if (dsd->isClusteringOn()) {
	cluster(anodeSideHits_);
	cluster(cathodeSideHits_);
      }
      m_Multiplicity_clustered[detid]->Fill(anodeSideHits_.size(),cathodeSideHits_.size());
            
      int anodecandidate = 0;
      int anodestrip = 0;
      int cathodecandidate = 0;
      int cathodestrip = 0;
      
      for(int i=0;i<anodeSideHits_.size();i++){
	double energy  = anodeSideHits_[i]->EPI();
	if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	  anodecandidate += 1;
	  anodestrip = anodeSideHits_[i]->PixelY();
	}
      }
      for(int j=0;j<cathodeSideHits_.size();j++){
	double energy  = cathodeSideHits_[j]->EPI();
	if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	  cathodecandidate += 1;
	  cathodestrip = cathodeSideHits_[j]->PixelX();
	}
      }

      if(!(anodecandidate==0 && cathodecandidate==0)){
	tmp_multiplicity_clustered[detid]->Fill(anodecandidate,cathodecandidate);
	if(1088<=exptime && exptime < 1098)tmp_multiplicity_clustered_timecut[detid]->Fill(anodecandidate,cathodecandidate);
      }
      if(anodecandidate == 1 && cathodecandidate==1){
	tmp_detectorimage_clustered[detid]->Fill(anodestrip,cathodestrip);
	if(1088<=exptime && exptime < 1098) tmp_detectorimage_clustered_timecut[detid]->Fill(anodestrip,cathodestrip);
      }

      //      bool energyconsistency = dsd->isEnergyConsistencyRequired();
      //      prioritySide_ = dsd->PrioritySide();
      /*
	centerPosition_ = detector->getCenterPosition();
	directionX_ = detector->getDirectionX();
	directionY_ = detector->getDirectionY();
	sizeX_ = detector->getSizeX();
	sizeY_ = detector->getSizeY();
	sizeZ_ = detector->getSizeZ();
	offsetX_ = detector->getOffsetX();
	offsetY_ = detector->getOffsetY();
	pixelPitchX_ = detector->getPixelPitchX();
	pixelPitchY_ = detector->getPixelPitchY();
      */

      
      if(m_AnalysisMode==1){
	int anodecandidate = 0;
	int anodeid = 0;
	int cathodecandidate = 0;
	int cathodeid = 0;
	
	for(int i=0;i<anodeSideHits_.size();i++){
	  double energy  = anodeSideHits_[i]->EPI();
	  if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	    anodecandidate += 1;
	    anodeid = i;
	  }
	}
	for(int j=0;j<cathodeSideHits_.size();j++){
	  double energy  = cathodeSideHits_[j]->EPI();
	  if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	    cathodecandidate += 1;
	    cathodeid = j;
	  }
	}
	if(anodecandidate == 1 && cathodecandidate==1){

	  DetectorHit_sptr merged = mergeDoubleSides(dsd,cathodeSideHits_[cathodeid], anodeSideHits_[anodeid]);
      
	  if (dsd->isEnergyConsistencyRequired()) {
	    if (!dsd->checkEnergyConsistency(merged->EPI(), cathodeSideHits_[cathodeid]->EPI())) {
	      return;
	    }
	    if (!dsd->checkEnergyConsistency(merged->EPI(), anodeSideHits_[anodeid]->EPI())) {
	      return;
	    }
	  }
	  
	  merged->setEnergy(merged->EPI());
	  reconstructedHits_.push_back(merged);
	}
	
	
      }else if(m_AnalysisMode==2){
	int anodecandidate = 0;
	int anodeid = 0;
	int cathodecandidate = 0;
	int cathodeid = 0;
	
	for(int i=0;i<anodeSideHits_.size();i++){
	  double energy  = anodeSideHits_[i]->EPI();
	  if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	    anodecandidate += 1;
	    anodeid = i;
	  }
	}
	for(int j=0;j<cathodeSideHits_.size();j++){
	  double energy  = cathodeSideHits_[j]->EPI();
	  if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	    cathodecandidate += 1;
	    cathodeid = j;
	  }
	}

	if(anodecandidate == 1 && cathodecandidate==1){
	  DetectorHit_sptr merged = mergeDoubleSides(dsd,cathodeSideHits_[cathodeid], anodeSideHits_[anodeid]);	  
	  if (dsd->isEnergyConsistencyRequired()) {
	    if (!dsd->checkEnergyConsistency(merged->EPI(), cathodeSideHits_[cathodeid]->EPI())) {
	      return;
	    }
	    if (!dsd->checkEnergyConsistency(merged->EPI(), anodeSideHits_[anodeid]->EPI())) {
	      return;
	    }
	  }
	  
	  merged->setEnergy(merged->EPI());
	  merged->setGrade(1);
	  reconstructedHits_.push_back(merged);
	  
	}else if(anodecandidate == 1 && cathodecandidate==0){
	  // cathode search from original distribution (before clustering)
	  int org_cathodecandidate = 0;
	  int org_cathodeid = 0;

	  for(int j=0;j<org_cathodeSideHits_.size();j++){
	    double energy  = org_cathodeSideHits_[j]->EPI();
	    if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	      org_cathodecandidate += 1;
	      org_cathodeid = j;
	    }
	  }

	  if(org_cathodecandidate==1){
	    DetectorHit_sptr merged = mergeDoubleSides(dsd,org_cathodeSideHits_[org_cathodeid], anodeSideHits_[anodeid]);	  
	    if (dsd->isEnergyConsistencyRequired()) {
	      if (!dsd->checkEnergyConsistency(merged->EPI(), org_cathodeSideHits_[org_cathodeid]->EPI())) {
		return;
	      }
	      if (!dsd->checkEnergyConsistency(merged->EPI(), anodeSideHits_[anodeid]->EPI())) {
		return;
	      }
	    }
	    
	    merged->setEnergy(merged->EPI());
	    merged->setGrade(2);
	    reconstructedHits_.push_back(merged);
	    
	  }
	  
	  
	}else if(anodecandidate == 0 && cathodecandidate==1){
	  // anode search from original distribution (before clustering)
	  int org_anodecandidate = 0;
	  int org_anodeid = 0;

	  for(int j=0;j<org_anodeSideHits_.size();j++){
	    double energy  = org_anodeSideHits_[j]->EPI();
	    if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	      org_anodecandidate += 1;
	      org_anodeid = j;
	    }
	  }

	  if(org_anodecandidate==1){
	    DetectorHit_sptr merged = mergeDoubleSides(dsd,cathodeSideHits_[cathodeid], org_anodeSideHits_[org_anodeid]);	  
	    if (dsd->isEnergyConsistencyRequired()) {
	      if (!dsd->checkEnergyConsistency(merged->EPI(), cathodeSideHits_[cathodeid]->EPI())) {
		return;
	      }
	      if (!dsd->checkEnergyConsistency(merged->EPI(), org_anodeSideHits_[org_anodeid]->EPI())) {
		return;
	      }
	    }
	    
	    merged->setEnergy(merged->EPI());
	    merged->setGrade(3);
	    reconstructedHits_.push_back(merged);
	    
	  }
	  

	}else{

	  // search from original distribution (before clustering)
	  int org_cathodecandidate = 0;
	  int org_cathodeid = 0;
	  for(int j=0;j<org_cathodeSideHits_.size();j++){	   	    
	    double energy  = org_cathodeSideHits_[j]->EPI();
	    if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	      org_cathodecandidate += 1;
	      org_cathodeid = j;
	    }
	  }
	  int org_anodecandidate = 0;
	  int org_anodeid = 0;
	  
	  for(int j=0;j<org_anodeSideHits_.size();j++){
	    double energy  = org_anodeSideHits_[j]->EPI();
	    if(m_Esearch_Ld < energy && energy < m_Esearch_Ud){
	      org_anodecandidate += 1;
	      org_anodeid = j;
	    }
	  }

	  if(org_cathodecandidate ==1 && org_anodecandidate==1){
	    DetectorHit_sptr merged = mergeDoubleSides(dsd,org_cathodeSideHits_[org_cathodeid], org_anodeSideHits_[org_anodeid]);	  
	    if (dsd->isEnergyConsistencyRequired()) {
	      if (!dsd->checkEnergyConsistency(merged->EPI(), org_cathodeSideHits_[org_cathodeid]->EPI())) {
		return;
	      }
	      if (!dsd->checkEnergyConsistency(merged->EPI(), org_anodeSideHits_[org_anodeid]->EPI())) {
		return;
	      }
	    }
	    
	    merged->setEnergy(merged->EPI());
	    merged->setGrade(4);
	    reconstructedHits_.push_back(merged);
	    
	  }
	  
	  
	}
	
	
	
      }else{
	reconstructDoubleSides(dsd,cathodeSideHits_, anodeSideHits_, reconstructedHits_);	
      }
      
      
      for(int j=0;j<(int)reconstructedHits_.size();j++){
	detector->insertReconstructedHit(reconstructedHits_[j]);
      }
      //      detector->reconstructHits();
    }
    
  }
  
  void OISTMakeDetectorHits_Muon::reconstructDoubleSides(RealDetectorUnit2DStrip* dsd,
							 const DetectorHitVector& hitsCathode,
							 const DetectorHitVector& hitsAnode,
							 DetectorHitVector& hitReconstructed)
  {
    if (hitsCathode.size()==1 && hitsAnode.size()==1) {
      DetectorHit_sptr hitCathode = hitsCathode[0];
      DetectorHit_sptr hitAnode = hitsAnode[0];
      DetectorHit_sptr merged = mergeDoubleSides(dsd,hitCathode, hitAnode);
      
      if (dsd->isEnergyConsistencyRequired()) {
	if (!dsd->checkEnergyConsistency(merged->EPI(), hitCathode->EPI())) {
	  return;
	}
	if (!dsd->checkEnergyConsistency(merged->EPI(), hitAnode->EPI())) {
	  return;
	}
      }
      
      merged->setEnergy(merged->EPI());
      hitReconstructed.push_back(merged);
    }
    
  }
  
  
  DetectorHit_sptr OISTMakeDetectorHits_Muon::mergeDoubleSides(comptonsoft::RealDetectorUnit2DStrip* dsd,
							       const DetectorHit_sptr hitCathode,
							       const DetectorHit_sptr hitAnode) const
  {
    PixelID spCathode = hitCathode->Pixel();
    PixelID spAnode = hitAnode->Pixel();
    PixelID pixel = spCathode.combine(spAnode);
    vector3_t position = dsd->Position(pixel);
    vector3_t localPosition = dsd->LocalPosition(pixel);
    DetectorHit_sptr hit(new DetectorHit((dsd->PrioritySide()==ElectrodeSide::Anode) ?
					 (*hitAnode) : 
					 (*hitCathode)));
    hit->setPosition(position);
    hit->setLocalPosition(localPosition);
    hit->setPixel(pixel);
    return hit;
  }
  
  /*
  comptonsoft::vector3_t OISTMakeDetectorHits_Muon::Position(int pixelX, int pixelY) const
  {
    const vector3_t pos = centerPosition_
      + (-0.5*sizeX_ + (offsetX_+(0.5+pixelX)*pixelPitchX_)) * directionX_
      + (-0.5*sizeY_ + (offsetY_+(0.5+pixelY)*pixelPitchY_)) * directionY_;
    return pos;
  }
  
  comptonsoft::vector3_t OISTMakeDetectorHits_Muon::LocalPosition(int pixelX, int pixelY) const
  {
    const vector3_t dirx(1.0, 0.0, 0.0);
    const vector3_t diry(0.0, 1.0, 0.0);
    const vector3_t pos =
      (-0.5*sizeX_ + (offsetX_+(0.5+pixelX)*pixelPitchX_)) * dirx
      + (-0.5*sizeY_ + (offsetY_+(0.5+pixelY)*pixelPitchY_)) * diry;
    return pos;
  }
  */

  //  ANLStatus OISTMakeDetectorHits_Muon::mod_init()
  //  {
  // VCSModule::mod_init();
  //  GetANLModule("OISTReadDataFile_Muon", &readDatafile_);
    //    return AS_OK;
  //  }

  void OISTMakeDetectorHits_Muon::cluster(comptonsoft::DetectorHitVector& hits) const
  {
    std::vector<std::list<DetectorHit_sptr>> groups;
    std::transform(hits.begin(), hits.end(), std::back_inserter(groups),
		   [](const DetectorHit_sptr& hit){
		     return std::list<DetectorHit_sptr>(1, hit);
		   });
    
    auto compair = [](const DetectorHit_sptr& hit1, const DetectorHit_sptr& hit2)-> bool {
      return hit1->EPI() > hit2->EPI();
    };
    
    bool merged = true;
    while (merged) {
      merged = false;
      auto groupIter = std::begin(groups);
      while (groupIter != std::end(groups)) {
	auto groupIter1 = groupIter + 1;
	while (groupIter1 != std::end(groups)) {
	  if (is_group_adjacent(*groupIter, *groupIter1)) {
	    groupIter->merge(*groupIter1, compair);
	    groupIter1 = groups.erase(groupIter1);
	    merged = true;
	  }
	  else {
	    ++groupIter1;
	  }
	}
	++groupIter;
      }
    }
    
    for (auto& group: groups) {
      group.sort(compair);
    }
    
    DetectorHitVector clusteredHits;
    for (auto& group: groups) {
      clusteredHits.push_back(DetectorHit_sptr(group.front()));
      auto hitIter=std::begin(group);
      ++hitIter;
      for (; hitIter!=std::end(group); ++hitIter) {
	clusteredHits.back()->mergeAdjacentSignal(**hitIter, DetectorHit::MergedPosition::KeepLeft);
      }
    }
    hits = std::move(clusteredHits);
  }
  
  
  
} /* namespace oistapp */
