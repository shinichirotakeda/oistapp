#ifndef OISTAPP_OISTDetectorImage_OISTCdTe_H
#define OISTAPP_OISTDetectorImage_OISTCdTe_H 1

#include "VCSModule.hh"

class TH2;


namespace anlgeant4 { class InitialInformation; }
namespace comptonsoft {class CSHitCollection;}
namespace oistapp {

  class OISTDetectorImage_OISTCdTe : public comptonsoft::VCSModule
  {
    DEFINE_ANL_MODULE(OISTDetectorImage_OISTCdTe, 1.1);
  public:
    OISTDetectorImage_OISTCdTe();  
    ~OISTDetectorImage_OISTCdTe() = default;
    
    anl::ANLStatus mod_startup();
    anl::ANLStatus mod_init();
    anl::ANLStatus mod_his();
    anl::ANLStatus mod_ana();
    
  private:
    comptonsoft::CSHitCollection* m_HitCollection;
    const anlgeant4::InitialInformation* m_InitialInfo;
    std::map<int, TH2*> m_Image;
    std::map<int, TH2*> m_ImageEcut;
    double energy_ld;
    double energy_ud;
  };
  
} /* namespace oistapp */

#endif /* OISTAPP_OISTDetectorImage_OISTCdTe_H */
