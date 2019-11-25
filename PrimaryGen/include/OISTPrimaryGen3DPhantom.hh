#ifndef OISTAPP_OISTPrimaryGen3DPhantom_H
#define OISTAPP_OISTPrimaryGen3DPhantom_H 1

#include "BasicPrimaryGen.hh"
#include "G4ThreeVector.hh"
#include "TFile.h"
#include "TH3.h"

namespace oistapp {

class OISTPrimaryGen3DPhantom : public anlgeant4::BasicPrimaryGen
{
  DEFINE_ANL_MODULE(OISTPrimaryGen3DPhantom, 1.0);
public:
  OISTPrimaryGen3DPhantom();

  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_ana();
  anl::ANLStatus mod_endrun();

protected:
  void setSourcePosition(G4ThreeVector v) { m_SourcePosition = v; }
  void setCenterDirection(G4ThreeVector v) { m_CenterDirection = v; }
  void calculateRotation();

  G4ThreeVector sampleDirection();
  G4ThreeVector samplePosition();

  G4ThreeVector SourcePosition() { return m_SourcePosition; }

private:
  G4ThreeVector m_SourcePosition;
  
  
  
  G4ThreeVector m_CenterDirection;
  G4double m_Theta0;
  G4double m_Theta1;
  G4double m_CosTheta0;
  G4double m_CosTheta1;
  G4double m_CoveringFactor;
  
  G4double m_Luminosity;

  std::string m_FileName;
  TFile *m_fin;
  std::string m_HistName;
  TH3 *m_inputDistribution;

  G4double m_Xmin;
  G4double m_Xmax;
  G4double m_Ymin;
  G4double m_Ymax;
  G4double m_Zmin;
  G4double m_Zmax;
  G4double offset_x;
  G4double offset_y;
  G4double offset_z;
};

}

#endif /* OISTAPP_OISTPrimaryGen3DPhantom_H */
