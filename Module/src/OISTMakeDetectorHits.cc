#include "OISTMakeDetectorHits.hh"
#include <iostream>
#include <boost/format.hpp>
#include "FlagDefinition.hh"


using namespace anl;
using namespace comptonsoft;

namespace oistapp
{
  
  void OISTMakeDetectorHits::doProcessing()
  {
    //    std::cout<< "OISTMakeDetectorHits::doProcessing()" << std::endl;


    
    DetectorSystem* detectorManager = getDetectorManager();
    for (auto& detector: detectorManager->getDetectors()) {

      RealDetectorUnit2DStrip* dsd = dynamic_cast<RealDetectorUnit2DStrip*>(detector.get());
      cathodeSideHits_.clear();
      anodeSideHits_.clear();
      reconstructedHits_.clear();
      
      int detid = detector->getID();      
      detector->selectHits();
      const int numhit = detector->NumberOfDetectorHits();
      int anodehit =0;
      int cathodehit =0;      
      for(int i=0;i<numhit;i++){
	DetectorHit_sptr hit = detector->getDetectorHit(i);
	if(hit->isFlags(flag::AnodeSide)){
	  anodeSideHits_.push_back(hit->clone());
	  anodehit++;
	}else if(hit->isFlags(flag::CathodeSide)){
	  cathodeSideHits_.push_back(hit->clone());
	  cathodehit++;
	}else{
	  std::cout << "undefined ..." << std::endl; 
	}
	
      }
      m_Multiplicity[detid]->Fill(anodehit,cathodehit);

      auto compairStrip = [](const DetectorHit_sptr& h1, const DetectorHit_sptr& h2)-> bool {
	return ((h1->isXStrip() && (h1->Pixel().X() < h2->Pixel().X()))
		|| (h1->isYStrip() && (h1->Pixel().Y() < h2->Pixel().Y())));
      };
      
      std::sort(anodeSideHits_.begin(), anodeSideHits_.end(), compairStrip);
      std::sort(cathodeSideHits_.begin(), cathodeSideHits_.end(), compairStrip);


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
      reconstructDoubleSides(dsd,cathodeSideHits_, anodeSideHits_, reconstructedHits_);

      for(int j=0;j<(int)reconstructedHits_.size();j++){
	detector->insertReconstructedHit(reconstructedHits_[j]);
      }
      //      detector->reconstructHits();
    }
    
  }

  void OISTMakeDetectorHits::reconstructDoubleSides(RealDetectorUnit2DStrip* dsd,
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

  
  DetectorHit_sptr OISTMakeDetectorHits::mergeDoubleSides(comptonsoft::RealDetectorUnit2DStrip* dsd,
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
  comptonsoft::vector3_t OISTMakeDetectorHits::Position(int pixelX, int pixelY) const
  {
    const vector3_t pos = centerPosition_
      + (-0.5*sizeX_ + (offsetX_+(0.5+pixelX)*pixelPitchX_)) * directionX_
      + (-0.5*sizeY_ + (offsetY_+(0.5+pixelY)*pixelPitchY_)) * directionY_;
    return pos;
  }
  
  comptonsoft::vector3_t OISTMakeDetectorHits::LocalPosition(int pixelX, int pixelY) const
  {
    const vector3_t dirx(1.0, 0.0, 0.0);
    const vector3_t diry(0.0, 1.0, 0.0);
    const vector3_t pos =
      (-0.5*sizeX_ + (offsetX_+(0.5+pixelX)*pixelPitchX_)) * dirx
      + (-0.5*sizeY_ + (offsetY_+(0.5+pixelY)*pixelPitchY_)) * diry;
    return pos;
  }
  */
  
  ANLStatus OISTMakeDetectorHits::mod_his()
  {
    
    VCSModule::mod_his();
    mkdir();
    
    DetectorSystem* detectorManager = getDetectorManager();
    
    for(int i=0;i<(detectorManager->NumberOfDetectors());i++){
      VRealDetectorUnit* detunit = detectorManager->getDetectorByIndex(i);
      int detid = detunit->getID();
      int pixelx = detunit->getNumPixelX();
      int pixely = detunit->getNumPixelY();
      TH2F *hist = 0;
      std::string name = (boost::format("multiplicity_%04d") % detid).str();
      hist = new TH2F(name.c_str(), "multiplicity", pixelx, -0.5, pixelx-0.5, pixely, -0.5, pixely-0.5);
      hist->GetXaxis()->SetTitle("Multiplicity(Anode)");
      hist->GetYaxis()->SetTitle("Multiplicity(Cathode)");
      m_Multiplicity[detid] = hist;
      
    }
    return AS_OK;
  }
  
  
} /* namespace oistapp */
