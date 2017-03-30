#ifndef OISTAPP_OISTPrimaryGenUltraMicroPhantom_H
#define OISTAPP_OISTPrimaryGenUltraMicroPhantom_H 1

#include "BasicPrimaryGen.hh"
#include "G4ThreeVector.hh"
#include "TFile.h"
#include "TH2.h"

namespace oistapp {

class OISTPrimaryGenUltraMicroPhantom : public anlgeant4::BasicPrimaryGen
{
  DEFINE_ANL_MODULE(OISTPrimaryGenUltraMicroPhantom, 1.0);
public:
  OISTPrimaryGenUltraMicroPhantom();

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

  G4double center_x;
  G4double center_y;
  G4double center_z;

  G4double rot;
  
};

}

#endif /* OISTAPP_OISTPrimaryGenUltraMicroPhantom_H */
