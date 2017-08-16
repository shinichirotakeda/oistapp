#include "OISTDetectorImage_OISTCdTe.hh"

#include <boost/format.hpp>
#include "TDirectory.h"
#include "TH2.h"
#include "AstroUnits.hh"
#include "CSHitCollection.hh"
#include "InitialInformation.hh"
#include "DetectorHit.hh"
#include "ConstructDetector.hh"

using namespace anl;
using namespace comptonsoft;

namespace oistapp
{

OISTDetectorImage_OISTCdTe::OISTDetectorImage_OISTCdTe()
  : m_HitCollection(0), m_InitialInfo(0),energy_ld(0), energy_ud(10000)
{
}

ANLStatus OISTDetectorImage_OISTCdTe::mod_startup()
{
  register_parameter(&energy_ld, "energy_min", 1, "keV");
  register_parameter(&energy_ud, "energy_max", 1, "keV");

  return AS_OK;
}

ANLStatus OISTDetectorImage_OISTCdTe::mod_init()
{

  VCSModule::mod_init();
  GetANLModuleNC("CSHitCollection", &m_HitCollection);
  GetANLModuleIFNC("InitialInformation", &m_InitialInfo);
  return AS_OK;
}

ANLStatus OISTDetectorImage_OISTCdTe::mod_his()
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
    std::string name = (boost::format("image_%04d") % detid).str();
    hist = new TH2F(name.c_str(), "image", pixelx, 0, pixelx, pixely, 0, pixely);
    TH2F *histecut = 0;
    name = (boost::format("image_ecut_%04d") % detid).str();
    histecut = new TH2F(name.c_str(), "image_ecut", pixelx, 0, pixelx, pixely, 0, pixely);
    
    m_Image[detid] = hist;
    m_ImageEcut[detid] = histecut;

  }
    
  return AS_OK;
}

ANLStatus OISTDetectorImage_OISTCdTe::mod_ana()
{
  typedef std::vector<DetectorHit_sptr> HitVector;

  
  HitVector& hitVec = m_HitCollection->getHits();
  
  for (HitVector::iterator it=hitVec.begin(); it!=hitVec.end(); ++it) {
    double energy = (*it)->Energy();
    double detid = (*it)->DetectorID();
    double pixelx = (*it)->PixelX();
    double pixely = (*it)->PixelY();
    m_Image[detid]->Fill(pixelx,pixely);

    if(pixelx == 24){
      if(15.0 <= energy/keV && energy/keV<=35.0){
	m_ImageEcut[detid]->Fill(pixelx,pixely);
      }      
    }else if(pixelx == 29){
      if(15.0 <= energy/keV && energy/keV<=35.0){
	m_ImageEcut[detid]->Fill(pixelx,pixely);
      }   
    }else if(pixelx == 32){
      if(15.0 <= energy/keV && energy/keV<=35.0){
	m_ImageEcut[detid]->Fill(pixelx,pixely);
      } 
    }
    else{
      if(energy_ld <= energy/keV && energy/keV<=energy_ud){
	m_ImageEcut[detid]->Fill(pixelx,pixely);
      }
    }
  }
  
  return AS_OK;
}

} /* namespace oistapp */
