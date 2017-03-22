#ifndef OISTAPP_OISTReadDataFile_COMP_H
#define OISTAPP_OISTReadDataFile_COMP_H 1

#include "ReadDataFile.hh"

#include <cstdint>
#include <memory>

class TChain;

namespace oistapp {

  class OISTReadDataFile_COMP : public comptonsoft::ReadDataFile
  {
    DEFINE_ANL_MODULE(OISTReadDataFile, 1.0);
  public:
    OISTReadDataFile_COMP() = default;
    ~OISTReadDataFile_COMP() = default;
    
    anl::ANLStatus mod_init();
    anl::ANLStatus mod_ana();

    unsigned long int getExpTime() const { return m_exptime; }
    
  private:
    TChain* m_Tree = nullptr;
    uint32_t m_NEvents = 0u;
    std::unique_ptr<std::unique_ptr<uint16_t[]>[]> m_ADC;
    std::unique_ptr<std::unique_ptr<uint16_t[]>[]> m_INDEX;  
    std::unique_ptr<uint16_t[]> m_HITNUM;
    std::unique_ptr<uint16_t[]> m_CMN;
    unsigned int m_UnixTime = 0;
    unsigned int m_LiveTime;
    unsigned int m_IntegralLiveTime;
    unsigned int m_Ti;

    unsigned long int m_exptime;
    unsigned int m_ext1pps;
    unsigned int m_msec_counter;
    
  };
  
} 

#endif
