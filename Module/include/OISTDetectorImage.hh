#ifndef OISTAPP_OISTDetectorImage_H
#define OISTAPP_OISTDetectorImage_H 1

#include "VCSModule.hh"

class TH1;


namespace anlgeant4 { class InitialInformation; }
namespace comptonsoft {class CSHitCollection;}
namespace oistapp {

  class OISTDetectorImage : public comptonsoft::VCSModule
  {
    DEFINE_ANL_MODULE(OISTDetectorImage, 1.1);
  public:
    OISTDetectorImage();  
    ~OISTDetectorImage() = default;
    
    anl::ANLStatus mod_startup();
    anl::ANLStatus mod_init();
    anl::ANLStatus mod_his();
    anl::ANLStatus mod_ana();
    
  private:
    comptonsoft::CSHitCollection* m_HitCollection;
    const anlgeant4::InitialInformation* m_InitialInfo;
    std::string m_EnergyBinType;
    int m_NumBinEnergy;
    double m_RangeEnergy1;
    double m_RangeEnergy2;
    std::map<std::string, TH1*> m_Responses;
    std::vector<std::string> m_Selections;
  };
  
} /* namespace oistapp */

#endif /* OISTAPP_OISTDetectorImage_H */
