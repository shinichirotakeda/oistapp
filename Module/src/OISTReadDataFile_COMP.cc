#include "OISTReadDataFile_COMP.hh"

#include <iostream>
#include <iomanip>
#include <sstream>

#include "TChain.h"

#include "DetectorReadoutModule.hh"
#include "MultiChannelData.hh"

using namespace anl;
using namespace comptonsoft;
namespace oistapp
{

ANLStatus OISTReadDataFile_COMP::mod_init()
{

  VCSModule::mod_init();
  ReadDataFile::mod_init();

  m_Tree = new TChain("eventtree");
  while (!wasLastFile()) {
    m_Tree->Add(nextFile().c_str());
  }
  
  m_NEvents = m_Tree->GetEntries();
  std::cout << "Total Event : " << m_NEvents << std::endl;
  
  int numASICs = 0;
  DetectorSystem* detectorManager = getDetectorManager();
  for (auto& readoutModule: detectorManager->getReadoutModules()) {
    numASICs += readoutModule->NumberOfReadoutSections();
  }
  std::cout << "Total readout ASICs : " << numASICs << std::endl;
  m_ADC.reset(new std::unique_ptr<uint16_t[]>[numASICs]);
  m_INDEX.reset(new std::unique_ptr<uint16_t[]>[numASICs]);
  m_CMN.reset(new uint16_t[numASICs]);
  m_HITNUM.reset(new uint16_t[numASICs]);

  int iASIC = 0;
  for (auto& readoutModule: detectorManager->getReadoutModules()) {
    for (auto& section: readoutModule->getReadoutSections()) {
      MultiChannelData* mcd = detectorManager->getMultiChannelData(section);
      int numChannels = mcd->NumberOfChannels();
      //m_ADC[iASIC].reset(new uint16_t[numChannels]);
      m_ADC[iASIC].reset(new uint16_t[2*numChannels]);
      m_INDEX[iASIC].reset(new uint16_t[2*numChannels]);
      

      std::ostringstream oss;
      oss << "adc" << iASIC;
      std::string branchName = oss.str();
      m_Tree->SetBranchAddress(branchName.c_str(), m_ADC[iASIC].get());
      std::cout << branchName << " " << numChannels << std::endl;

      oss.str("");
      oss << "index" << iASIC;
      branchName = oss.str();
      m_Tree->SetBranchAddress(branchName.c_str(), m_INDEX[iASIC].get());
      std::cout << branchName << std::endl;

      oss.str("");
      oss << "hitnum" << iASIC;
      branchName = oss.str();
      m_Tree->SetBranchAddress(branchName.c_str(), &m_HITNUM[iASIC]);
      std::cout << branchName << std::endl;
      
      oss.str("");
      oss << "cmn" << iASIC;
      branchName = oss.str();
      m_Tree->SetBranchAddress(branchName.c_str(), &m_CMN[iASIC]);
      std::cout << branchName << std::endl;
      
      iASIC++;
    }
  }

  m_Tree->SetBranchAddress("unixtime", &m_UnixTime);
  m_Tree->SetBranchAddress("livetime", &m_LiveTime);
  m_Tree->SetBranchAddress("integral_livetime", &m_IntegralLiveTime);
  m_Tree->SetBranchAddress("ti", &m_Ti);

  m_Tree->SetBranchAddress("ext1pps", &m_ext1pps);
  m_Tree->SetBranchAddress("msec_counter", &m_msec_counter);

  return AS_OK;
}

ANLStatus OISTReadDataFile_COMP::mod_ana()
{
  static unsigned int iEvent = 0;
  if(iEvent == m_NEvents) {
    return AS_QUIT;
  }
  
  m_Tree->GetEntry(iEvent);

  setTime(m_UnixTime);
  m_exptime = (((unsigned long int)m_ext1pps)<<32) | (unsigned long int)m_msec_counter;
  
  DetectorSystem* detectorManager = getDetectorManager();
  int iASIC = 0;
  for (auto& readoutModule: detectorManager->getReadoutModules()) {
    for (auto& section: readoutModule->getReadoutSections()) {
      MultiChannelData* mcd = detectorManager->getMultiChannelData(section);
      int numChannels = mcd->NumberOfChannels();
      //      for (int i=0; i<numChannels; i++) {
      for (int i=0; i<2*numChannels; i++) {
	uint16_t data = m_ADC[iASIC][i];
	uint16_t index = m_INDEX[iASIC][i];
	uint16_t hitnum = m_HITNUM[iASIC];
	uint16_t cmn = m_CMN[iASIC];
	//	std::cout << index << " " << data << " " << cmn << " " << hitnum << std::endl;

	if((i==0 && hitnum != 0) || index!=0){
	  if(index%2==0){
	    mcd->setRawADC(index/2, data);
	    mcd->setDataValid(index/2,1);
	    mcd->setCommonModeNoise(cmn);
	  }
	}
      }
      iASIC++;
    }
  }
  
  iEvent++;
  return ReadDataFile::mod_ana();
}

} /* namespace comptonsoft */
