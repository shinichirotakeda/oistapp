#ifndef OISTAPP_OISTMakeDetectorHits_COMP_H
#define OISTAPP_OISTMakeDetectorHits_COMP_H 1

#include "CSTypes.hh"
#include "DetectorHit.hh"
#include "SelectHits.hh"
#include "VRealDetectorUnit.hh"
#include "RealDetectorUnit2DStrip.hh"
#include "TH2.h"

namespace oistapp {

class OISTMakeDetectorHits_COMP : public comptonsoft::SelectHits
{
  DEFINE_ANL_MODULE(OISTMakeDetectorHits_COMP, 1.0);
public:
  OISTMakeDetectorHits_COMP() = default;
  ~OISTMakeDetectorHits_COMP() = default;

  anl::ANLStatus mod_his();
  

private:
  void doProcessing();

  int NumberOfCathodeSideHits() const { return cathodeSideHits_.size(); }
  comptonsoft::DetectorHit_sptr getCathodeSideHit(int i) { return cathodeSideHits_[i]; }
  int NumberOfAnodeSideHits() const { return anodeSideHits_.size(); }
  comptonsoft::DetectorHit_sptr getAnodeSideHit(int i) { return anodeSideHits_[i]; }
  
  
  void reconstructDoubleSides(comptonsoft::RealDetectorUnit2DStrip* dsd,
			      const comptonsoft::DetectorHitVector& hitsCathode,
			      const comptonsoft::DetectorHitVector& hitsAnode,
			      comptonsoft::DetectorHitVector& hitReconstructed);
  
  comptonsoft::DetectorHit_sptr mergeDoubleSides(comptonsoft::RealDetectorUnit2DStrip* dsd,
						 const comptonsoft::DetectorHit_sptr hitCathode,
						 const comptonsoft::DetectorHit_sptr hitAnode) const;
  
  void cluster(comptonsoft::DetectorHitVector& hits) const;


  //  comptonsoft::vector3_t Position(int pixelX, int pixelY) const;
  //  comptonsoft::vector3_t LocalPosition(int pixelX, int pixelY) const;
  /*
  comptonsoft::vector3_t centerPosition_;
  comptonsoft::vector3_t directionX_;
  comptonsoft::vector3_t directionY_;
  double sizeX_;
  double sizeY_;
  double sizeZ_;
  double offsetX_;
  double offsetY_;
  double pixelPitchX_;
  double pixelPitchY_;
  */

  comptonsoft::DetectorHitVector reconstructedHits_;
  comptonsoft::DetectorHitVector cathodeSideHits_;
  comptonsoft::DetectorHitVector anodeSideHits_;
  
  std::map<int, TH2*> m_Multiplicity_org;
  std::map<int, TH2*> m_Multiplicity_clustered;
  
};


  
} /* namespace comptonsoft */

#endif /* OISTAPP_OISTMakeDetectorHits_COMP_H */
