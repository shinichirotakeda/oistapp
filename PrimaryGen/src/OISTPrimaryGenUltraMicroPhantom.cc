#include "OISTPrimaryGenUltraMicroPhantom.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"
#include "VANLGeometry.hh"
#include "AstroUnits.hh"
#include "TMath.h"

using namespace anl;
using namespace anlgeant4;
using namespace oistapp;

OISTPrimaryGenUltraMicroPhantom::OISTPrimaryGenUltraMicroPhantom()
  : m_SourcePosition(0.0, 0.0, 0.0),
    m_CenterDirection(0.0, 0.0, -1.0),
    m_Theta0(0.0), m_Theta1(pi), m_CosTheta0(1.0), m_CosTheta1(-1.0),
    m_CoveringFactor(1.0), m_Luminosity(1.0*(erg/s))
{
  add_alias("OISTPrimaryGenUltraMicroPhantom");
}


ANLStatus OISTPrimaryGenUltraMicroPhantom::mod_startup()
{
  BasicPrimaryGen::mod_startup();

  enablePowerLawInput();
  register_parameter(&m_SourcePosition, "Source position",
                     LengthUnit(), LengthUnitName());
  set_parameter_description("Position of the source.");
  register_parameter(&m_CenterDirection, "Center direction");
  set_parameter_description("Center direction of the primaries.");
  register_parameter(&m_Theta0, "theta min", 1.0, "radian");
  set_parameter_description("Minimum angle between the primary direction and the center direction.");
  register_parameter(&m_Theta1, "theta max", 1.0, "radian");
  set_parameter_description("Maximum angle between the primary direction and the center direction.");
  register_parameter(&m_Luminosity, "Luminosity", erg/s, "erg/s");
  set_parameter_description("Energy luminosity of the point source. This parameter is used only for calculating real time correspoing to a simulation.");

  register_parameter(&m_FileName, "Input file name");
  register_parameter(&m_HistName, "Histgram name");
  register_parameter(&rot,"rotation degree");
  return AS_OK;
}


ANLStatus OISTPrimaryGenUltraMicroPhantom::mod_init()
{
  using std::cos;
  
  BasicPrimaryGen::mod_init();
  m_CenterDirection = m_CenterDirection.unit();

  const G4double posx = m_SourcePosition.x();
  const G4double posy = m_SourcePosition.y();
  const G4double posz = m_SourcePosition.z();

  const G4double dirx = m_CenterDirection.x();
  const G4double diry = m_CenterDirection.y();
  const G4double dirz = m_CenterDirection.z();

  m_CosTheta0 = cos(m_Theta0);
  m_CosTheta1 = cos(m_Theta1);
  m_CoveringFactor = 0.5*(m_CosTheta0-m_CosTheta1);
  
  G4cout << "--------" << G4endl;
  G4cout << "PrimaryGen status (point source)" << G4endl;
  G4cout << "  Source Position: "
         << posx/cm << " " << posy/cm << " " << posz/cm << " cm" <<G4endl;
  printSpectralInfo();
  G4cout << "  Direction: "
         << dirx << " " << diry << " " << dirz << '\n' 
         << "    theta: " << m_Theta0/degree << " - " << m_Theta1/degree
         << " deg ( covering factor: " << m_CoveringFactor << " )"<< G4endl;


  m_fin = new TFile(m_FileName.c_str());
  m_inputDistribution = (TH2 *)m_fin->Get(m_HistName.c_str());

  m_Xmin =  m_inputDistribution->GetXaxis()->GetXmin();
  m_Xmax =  m_inputDistribution->GetXaxis()->GetXmax();
  m_Ymin =  m_inputDistribution->GetYaxis()->GetXmin();
  m_Ymax =  m_inputDistribution->GetYaxis()->GetXmax();

  center_x = posx/cm;
  center_y = posy/cm;
  center_z = posz/cm;
  

  return AS_OK;
}


ANLStatus OISTPrimaryGenUltraMicroPhantom::mod_ana()
{
  const G4ThreeVector position = samplePosition();
  const G4ThreeVector direction = sampleDirection();
  const G4double energy = sampleEnergy();

  setPrimary(position, energy, direction);

  if (PolarizationMode()==0) {
    setUnpolarized();
  }

  return BasicPrimaryGen::mod_ana();
}


G4ThreeVector OISTPrimaryGenUltraMicroPhantom::sampleDirection()
{
  G4double phi = twopi * G4UniformRand();
  G4double cosTheta = m_CosTheta0+(m_CosTheta1-m_CosTheta0)*G4UniformRand();
  G4double sinTheta = sqrt(1.0-cosTheta*cosTheta);
  G4ThreeVector direction(sinTheta*cos(phi), sinTheta*sin(phi), cosTheta);
  direction.rotateUz(m_CenterDirection);
  return direction;
}


G4ThreeVector OISTPrimaryGenUltraMicroPhantom::samplePosition()
{

  G4double posx, posy,posz;
  int xbin,ybin;

  while(1){
    posy = m_Xmin + G4UniformRand()*(m_Xmax-m_Xmin);
    posz = m_Ymin + G4UniformRand()*(m_Ymax-m_Ymin);
    xbin = m_inputDistribution->GetXaxis()->FindBin(posy);
    ybin = m_inputDistribution->GetYaxis()->FindBin(posz);
    int value = m_inputDistribution->GetBinContent(xbin,ybin);
    
    if(value>0.){
      posx = -0.5 + 1.0*G4UniformRand();
      break;
    }else{
      continue;
    }
    
  }

  G4double rot_y = posy*TMath::Cos(TMath::Pi()/180.*rot)-posz*TMath::Sin(TMath::Pi()/180.*rot);
  G4double rot_z = posy*TMath::Sin(TMath::Pi()/180.*rot)+posz*TMath::Cos(TMath::Pi()/180.*rot);
  
  m_SourcePosition.setX(posx*cm + center_x*cm);
  m_SourcePosition.setY(rot_y*cm + center_y*cm);
  m_SourcePosition.setZ(rot_z*cm + center_z*cm);
  return m_SourcePosition;
}


ANLStatus OISTPrimaryGenUltraMicroPhantom::mod_endrun()
{
  G4double realTime = 0.;
  G4double pflux = 0.;
  if (m_CoveringFactor != 0.0) {
    realTime = (TotalEnergy()/m_CoveringFactor)/m_Luminosity;
    pflux = (Number()/m_CoveringFactor)/realTime;
  }

  G4cout.setf(std::ios::scientific);
  G4cout << "PSPrimaryGen::mod_endrun \n"
         << "  Number: " << Number() << "\n"
         << "  Luminosity: " << m_Luminosity/(erg/s) << " erg/s\n"
         << "  Total Energy: " << TotalEnergy()/keV << " keV = "
         << TotalEnergy()/erg << " erg\n"
         << "  Covering Factor: " << m_CoveringFactor << "\n"
         << "  Real Time: " << realTime/s << " s"
         << "  Photon rate: " << pflux/(1.0/s) << " photons/s\n"
         << G4endl;
  G4cout.unsetf(std::ios::scientific);

  return AS_OK;
}
