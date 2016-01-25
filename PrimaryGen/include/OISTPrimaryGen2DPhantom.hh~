#ifndef OISTAPP_OISTPrimaryGen2DPhantom_H
#define OISTAPP_OISTPrimaryGen2DPhantom_H 1

#include "BasicPrimaryGen.hh"
#include "G4ThreeVector.hh"
#include "TFile.h"
#include "TH2.h"

namespace oistapp {

class OISTPrimaryGen2DPhantom : public anlgeant4::BasicPrimaryGen
{
  DEFINE_ANL_MODULE(OISTPrimaryGen2DPhantom, 1.0);
public:
  OISTPrimaryGen2DPhantom();

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
  TH2 *m_inputDistribution;

  G4double m_Xmin;
  G4double m_Xmax;
  G4double m_Ymin;
  G4double m_Ymax;
  
};

}

#endif /* OISTAPP_OISTPrimaryGen2DPhantom_H */
