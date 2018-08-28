#include "OISTMakeDetectorHits_OISTCdTe.hh"
#include <iostream>
#include <boost/format.hpp>
#include "FlagDefinition.hh"
#include "AstroUnits.hh"

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
  
  void OISTMakeDetectorHits_OISTCdTe::doProcessing()
  {
    //    std::cout<< "OISTMakeDetectorHits_OISTCdTe::doProcessing()" << std::endl;


    
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
      m_Multiplicity_org[detid]->Fill(anodeSideHits_.size(),cathodeSideHits_.size());

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

      if(cathodeSideHits_.size()==2){
	int pixel0 = cathodeSideHits_[0]->Pixel().X();
	int pixel1 = cathodeSideHits_[1]->Pixel().X();
	if(pixel0==23 && pixel1==25){
	  double energy = (cathodeSideHits_[0]->EPI())+(cathodeSideHits_[1]->EPI());
	  splithit_p_ch24->Fill(cathodeSideHits_[0]->EPI()/keV,cathodeSideHits_[1]->EPI()/keV);
	  energy_p_ch24->Fill((cathodeSideHits_[0]->EPI()+cathodeSideHits_[1]->EPI())/keV);
	  cathodeSideHits_.clear();
	  DetectorHit_sptr hit (new DetectorHit());
	  hit->setEPI(energy);
	  hit->setEnergy(energy);
	  hit->setPixel(24,-1);
	  hit->setDetectorID(detid);
	  cathodeSideHits_.push_back(hit->clone());
	  
	}
	if(pixel0==28 && pixel1==30){
	  double energy = (cathodeSideHits_[0]->EPI())+(cathodeSideHits_[1]->EPI());
	  splithit_p_ch29->Fill(cathodeSideHits_[0]->EPI()/keV,cathodeSideHits_[1]->EPI()/keV);
	  energy_p_ch29->Fill((cathodeSideHits_[0]->EPI()+cathodeSideHits_[1]->EPI())/keV);
	  cathodeSideHits_.clear();
	  DetectorHit_sptr hit (new DetectorHit());
	  hit->setEPI(energy);
	  hit->setEnergy(energy);
	  hit->setPixel(29,-1);
	  hit->setDetectorID(detid);
	  cathodeSideHits_.push_back(hit->clone());

	}
	if(pixel0==31 && pixel1==33){
	  double energy = (cathodeSideHits_[0]->EPI())+(cathodeSideHits_[1]->EPI());
	  splithit_p_ch32->Fill(cathodeSideHits_[0]->EPI()/keV,cathodeSideHits_[1]->EPI()/keV);
	  energy_p_ch32->Fill((cathodeSideHits_[0]->EPI()+cathodeSideHits_[1]->EPI())/keV);
	  cathodeSideHits_.clear();
	  DetectorHit_sptr hit (new DetectorHit());
	  hit->setEPI(energy);
	  hit->setEnergy(energy);
	  hit->setPixel(32,-1);
	  hit->setDetectorID(detid);
	  cathodeSideHits_.push_back(hit->clone());
	}
	
      }
      if(anodeSideHits_.size()==2){
	int pixel0 = anodeSideHits_[0]->Pixel().Y();
	int pixel1 = anodeSideHits_[1]->Pixel().Y();
	if(pixel0==2 && pixel1==4){
	  double energy = (anodeSideHits_[0]->EPI())+(anodeSideHits_[1]->EPI());
	  splithit_n_ch03->Fill(anodeSideHits_[0]->EPI()/keV,anodeSideHits_[1]->EPI()/keV);
	  energy_n_ch03->Fill((anodeSideHits_[0]->EPI()+anodeSideHits_[1]->EPI())/keV);
	  anodeSideHits_.clear();
	  DetectorHit_sptr hit (new DetectorHit());
	  hit->setEPI(energy);
	  hit->setEnergy(energy);
	  hit->setPixel(-1,3);
	  hit->setDetectorID(detid);
	  anodeSideHits_.push_back(hit->clone());
	}
	if(pixel0==13 && pixel1==15){
	  double energy = (anodeSideHits_[0]->EPI())+(anodeSideHits_[1]->EPI());
	  splithit_n_ch14->Fill(anodeSideHits_[0]->EPI()/keV,anodeSideHits_[1]->EPI()/keV);
	  energy_n_ch14->Fill((anodeSideHits_[0]->EPI()+anodeSideHits_[1]->EPI())/keV);
	  anodeSideHits_.clear();
	  DetectorHit_sptr hit (new DetectorHit());
	  hit->setEPI(energy);
	  hit->setEnergy(energy);
	  hit->setPixel(-1,14);
	  hit->setDetectorID(detid);
	  anodeSideHits_.push_back(hit->clone());
	}
	if(pixel0==16 && pixel1==18){
	  double energy = (anodeSideHits_[0]->EPI())+(anodeSideHits_[1]->EPI());
	  splithit_n_ch17->Fill(anodeSideHits_[0]->EPI()/keV,anodeSideHits_[1]->EPI()/keV);
	  energy_n_ch17->Fill((anodeSideHits_[0]->EPI()+anodeSideHits_[1]->EPI())/keV);
	  anodeSideHits_.clear();
	  DetectorHit_sptr hit (new DetectorHit());
	  hit->setEPI(energy);
	  hit->setEnergy(energy);
	  hit->setPixel(-1,17);
	  hit->setDetectorID(detid);
	  anodeSideHits_.push_back(hit->clone());
	}
      }

      reconstructDoubleSides(dsd,cathodeSideHits_, anodeSideHits_, reconstructedHits_);
      
      for(int j=0;j<(int)reconstructedHits_.size();j++){
	detector->insertReconstructedHit(reconstructedHits_[j]);
      }
      //      detector->reconstructHits();
    }
    
  }

  void OISTMakeDetectorHits_OISTCdTe::reconstructDoubleSides(RealDetectorUnit2DStrip* dsd,
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

  
  DetectorHit_sptr OISTMakeDetectorHits_OISTCdTe::mergeDoubleSides(comptonsoft::RealDetectorUnit2DStrip* dsd,
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
  comptonsoft::vector3_t OISTMakeDetectorHits_OISTCdTe::Position(int pixelX, int pixelY) const
  {
    const vector3_t pos = centerPosition_
      + (-0.5*sizeX_ + (offsetX_+(0.5+pixelX)*pixelPitchX_)) * directionX_
      + (-0.5*sizeY_ + (offsetY_+(0.5+pixelY)*pixelPitchY_)) * directionY_;
    return pos;
  }
  
  comptonsoft::vector3_t OISTMakeDetectorHits_OISTCdTe::LocalPosition(int pixelX, int pixelY) const
  {
    const vector3_t dirx(1.0, 0.0, 0.0);
    const vector3_t diry(0.0, 1.0, 0.0);
    const vector3_t pos =
      (-0.5*sizeX_ + (offsetX_+(0.5+pixelX)*pixelPitchX_)) * dirx
      + (-0.5*sizeY_ + (offsetY_+(0.5+pixelY)*pixelPitchY_)) * diry;
    return pos;
  }
  */
  
  ANLStatus OISTMakeDetectorHits_OISTCdTe::mod_his()
  {
    
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
      
    }

    splithit_p_ch24 = new TH2D("splithit_p_ch24","splithit_p_ch24",250,-0.5,249.5,250,-0.5,249.5);
    splithit_p_ch29 = new TH2D("splithit_p_ch29","splithit_p_ch29",250,-0.5,249.5,250,-0.5,249.5);
    splithit_p_ch32 = new TH2D("splithit_p_ch32","splithit_p_ch32",250,-0.5,249.5,250,-0.5,249.5);
    splithit_n_ch03 = new TH2D("splithit_n_ch03","splithit_n_ch03",250,-0.5,249.5,250,-0.5,249.5);
    splithit_n_ch14 = new TH2D("splithit_n_ch14","splithit_n_ch14",250,-0.5,249.5,250,-0.5,249.5);
    splithit_n_ch17 = new TH2D("splithit_n_ch17","splithit_n_ch17",250,-0.5,249.5,250,-0.5,249.5);
    energy_p_ch24 = new TH1D("energy_p_ch24","energy_p_ch24",250,-0.5,249.5);
    energy_p_ch29 = new TH1D("energy_p_ch29","energy_p_ch29",250,-0.5,249.5);
    energy_p_ch32 = new TH1D("energy_p_ch32","energy_p_ch32",250,-0.5,249.5);
    energy_n_ch03 = new TH1D("energy_n_ch03","energy_n_ch03",250,-0.5,249.5);
    energy_n_ch14 = new TH1D("energy_n_ch14","energy_n_ch14",250,-0.5,249.5);
    energy_n_ch17 = new TH1D("energy_n_ch17","energy_n_ch17",250,-0.5,249.5);
    
    return AS_OK;
  }
  

  void OISTMakeDetectorHits_OISTCdTe::cluster(comptonsoft::DetectorHitVector& hits) const
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
