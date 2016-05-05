#ifndef OISTAPP_OISTReadDataFile_NT_H
#define OISTAPP_OISTReadDataFile_NT_H 1

#include "ReadDataFile.hh"

#include <cstdint>
#include <memory>

class TChain;

namespace oistapp {

  class OISTReadDataFile_NT : public comptonsoft::ReadDataFile
  {
    DEFINE_ANL_MODULE(OISTReadDataFile_NT, 1.0);
  public:
    OISTReadDataFile_NT() = default;
    ~OISTReadDataFile_NT() = default;
    
    anl::ANLStatus mod_init();
    anl::ANLStatus mod_ana();
    
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
    
  };
  
} 

#endif
