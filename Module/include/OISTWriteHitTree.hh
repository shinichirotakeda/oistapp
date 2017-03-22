#ifndef OISTAPP_OISTWriteHitTree_H
#define OISTAPP_OISTWriteHitTree_H 1

#include "VCSModule.hh"
#include "CSHitCollection.hh"
#include <memory>

#include "OISTReadDataFile_COMP.hh"

class TTree;


namespace comptonsoft {
class CSHitCollection;
}

namespace anlgeant4 {
class InitialInformation;
}

namespace oistapp {

class OISTHitTreeIOWithInitialInfo;


/**
 * 
 * @author Hirokazu Odaka
 * @date 2008-08-28
 * @date 2014-11-29
 */
  class OISTWriteHitTree : public comptonsoft::VCSModule
{
  DEFINE_ANL_MODULE(OISTWriteHitTree, 2.0);
public:
  OISTWriteHitTree();
  ~OISTWriteHitTree() = default;
  
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_his();
  anl::ANLStatus mod_ana();

private:

  const oistapp::OISTReadDataFile_COMP* readDatafile_;
  

  const comptonsoft::CSHitCollection* hitCollection_;
  const anlgeant4::InitialInformation* initialInfo_;
  TTree* hittree_;
  std::unique_ptr<OISTHitTreeIOWithInitialInfo> treeIO_;

  unsigned long int exptime;
};

} /* namespace oistapp */

#endif /* OISTAPP_OISTWriteHitTree_H */
