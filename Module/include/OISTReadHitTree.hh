#ifndef OISTAPP_OISTReadHitTree_H
#define OISTAPP_OISTReadHitTree_H 1

#include "VCSModule.hh"
#include "InitialInformation.hh"

#include <vector>
#include <string>
#include <cstdint>
#include "DetectorHit_sptr.hh"
#include "CSHitCollection.hh"

using namespace comptonsoft;

class TChain;

namespace oistapp {

class OISTHitTreeIOWithInitialInfo;

/**
 * @author Hitokazu Odaka
 * @date 2014-11-30
 */
class OISTReadHitTree : public VCSModule, public anlgeant4::InitialInformation
{
  DEFINE_ANL_MODULE(OISTReadHitTree, 2.0);
public:
  OISTReadHitTree();
  ~OISTReadHitTree();
  
  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_ana();

  unsigned long int getExpTime() const {return exptime_;}
  
protected:
  virtual void insertHit(const DetectorHit_sptr& hit);
  
private:
  std::vector<std::string> fileList_;

  TChain* hittree_;
  int64_t numEntries_ = 0;
  int64_t entryIndex_ = 0;

  CSHitCollection* hitCollection_;
  std::unique_ptr<OISTHitTreeIOWithInitialInfo> treeIO_;

  unsigned long int exptime_;
  
};

} /* namespace oistapp */

#endif /* OISTAPP_OISTReadHitTree_H */
