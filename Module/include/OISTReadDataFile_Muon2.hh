#ifndef OISTAPP_OISTReadDataFile_Muon2_H
#define OISTAPP_OISTReadDataFile_Muon2_H 1

#include "ReadDataFile.hh"

#include <cstdint>
#include <memory>

class TChain;

namespace oistapp {

  class OISTReadDataFile_Muon2 : public comptonsoft::ReadDataFile
  {
    DEFINE_ANL_MODULE(OISTReadDataFile, 1.0);
  public:
    OISTReadDataFile_Muon2() = default;
    ~OISTReadDataFile_Muon2() = default;
    
    anl::ANLStatus mod_init();
    anl::ANLStatus mod_ana();

    unsigned long int getExpTime() const { return m_exptime; }
    
  private:

    
    TChain* m_Tree = nullptr;
    uint32_t m_NEvents = 0u;
    std::unique_ptr<std::unique_ptr<int[]>[]> m_ADC;
    std::unique_ptr<std::unique_ptr<uint16_t[]>[]> m_INDEX;  
    std::unique_ptr<uint16_t[]> m_HITNUM;
    std::unique_ptr<int[]> m_CMN;
    unsigned int m_UnixTime = 0;
    unsigned int m_LiveTime;
    unsigned int m_IntegralLiveTime;
    unsigned int m_Ti;

    unsigned long int m_exptime;
    
  };
  
} 

#endif
