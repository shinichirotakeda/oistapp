#include "OISTPrimaryGen3DPhantom.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"
#include "VANLGeometry.hh"
#include "AstroUnits.hh"

using namespace anl;
using namespace anlgeant4;
using namespace oistapp;

OISTPrimaryGen3DPhantom::OISTPrimaryGen3DPhantom()
  : m_SourcePosition(0.0, 0.0, 0.0),
    m_CenterDirection(0.0, 0.0, -1.0),
    m_Theta0(0.0), m_Theta1(pi), m_CosTheta0(1.0), m_CosTheta1(-1.0),
    m_CoveringFactor(1.0), m_Luminosity(1.0*(erg/s))
{
  add_alias("OISTPrimaryGen3DPhantom");
}


ANLStatus OISTPrimaryGen3DPhantom::mod_startup()
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

  return AS_OK;
}


ANLStatus OISTPrimaryGen3DPhantom::mod_init()
{
  using std::cos;
  
  BasicPrimaryGen::mod_init();
  m_CenterDirection = m_CenterDirection.unit();

  offset_x = m_SourcePosition.x();
  offset_y = m_SourcePosition.y();
  offset_z = m_SourcePosition.z();

  const G4double dirx = m_CenterDirection.x();
  const G4double diry = m_CenterDirection.y();
  const G4double dirz = m_CenterDirection.z();

  m_CosTheta0 = cos(m_Theta0);
  m_CosTheta1 = cos(m_Theta1);
  m_CoveringFactor = 0.5*(m_CosTheta0-m_CosTheta1);
  
  G4cout << "--------" << G4endl;
  G4cout << "PrimaryGen status (point source)" << G4endl;
  G4cout << "  Source Position: "
         << offset_x/cm << " " << offset_y/cm << " " << offset_z/cm << " cm" <<G4endl;
  printSpectralInfo();
  G4cout << "  Direction: "
         << dirx << " " << diry << " " << dirz << '\n' 
         << "    theta: " << m_Theta0/degree << " - " << m_Theta1/degree
         << " deg ( covering factor: " << m_CoveringFactor << " )"<< G4endl;


  m_fin = new TFile(m_FileName.c_str());
  m_inputDistribution = (TH3 *)m_fin->Get(m_HistName.c_str());

  m_Xmin =  m_inputDistribution->GetXaxis()->GetXmin();
  m_Xmax =  m_inputDistribution->GetXaxis()->GetXmax();
  m_Ymin =  m_inputDistribution->GetYaxis()->GetXmin();
  m_Ymax =  m_inputDistribution->GetYaxis()->GetXmax();
  m_Zmin =  m_inputDistribution->GetZaxis()->GetXmin();
  m_Zmax =  m_inputDistribution->GetZaxis()->GetXmax();

  return AS_OK;
}


ANLStatus OISTPrimaryGen3DPhantom::mod_ana()
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


G4ThreeVector OISTPrimaryGen3DPhantom::sampleDirection()
{
  G4double phi = twopi * G4UniformRand();
  G4double cosTheta = m_CosTheta0+(m_CosTheta1-m_CosTheta0)*G4UniformRand();
  G4double sinTheta = sqrt(1.0-cosTheta*cosTheta);
  G4ThreeVector direction(sinTheta*cos(phi), sinTheta*sin(phi), cosTheta);
  direction.rotateUz(m_CenterDirection);
  return direction;
}


G4ThreeVector OISTPrimaryGen3DPhantom::samplePosition()
{

  G4double posx, posy,posz;
  int xbin,ybin,zbin;

  while(1){
    posx = m_Xmin + G4UniformRand()*(m_Xmax-m_Xmin);
    posy = m_Ymin + G4UniformRand()*(m_Ymax-m_Ymin);
    posz = m_Zmin + G4UniformRand()*(m_Zmax-m_Zmin);
    xbin = m_inputDistribution->GetXaxis()->FindBin(posx);
    ybin = m_inputDistribution->GetYaxis()->FindBin(posy);
    zbin = m_inputDistribution->GetZaxis()->FindBin(posz);
    int value = m_inputDistribution->GetBinContent(xbin,ybin,zbin);
    
    if(value>0.){
      break;
    }else{
      continue;
    }
    
  }
  
  m_SourcePosition.setX(posx*cm+offset_x);
  m_SourcePosition.setY(posy*cm+offset_y);
  m_SourcePosition.setZ(posz*cm+offset_z);
  return m_SourcePosition;
}


ANLStatus OISTPrimaryGen3DPhantom::mod_endrun()
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
