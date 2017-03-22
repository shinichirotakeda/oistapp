#ifndef OISTAPP_OISTWriteComptonEventTree_H
#define OISTAPP_OISTWriteComptonEventTree_H 1

#include "VCSModule.hh"
#include "EventReconstruction.hh"
#include "OISTReadHitTree.hh"

using namespace comptonsoft;

class TTree;

namespace anlgeant4 {
class InitialInformation;
}

namespace oistapp {


class OISTComptonEventTreeIOWithInitialInfo;

class OISTWriteComptonEventTree : public VCSModule
{
  DEFINE_ANL_MODULE(OISTWriteComptonEventTree, 2.0);
public:
  OISTWriteComptonEventTree();
  ~OISTWriteComptonEventTree();

  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_his();
  anl::ANLStatus mod_ana();

protected:
  TTree * cetree_;
  
private:
  EventReconstruction* eventReconstruction_;
  const anlgeant4::InitialInformation* initialInfo_;
  std::unique_ptr<OISTComptonEventTreeIOWithInitialInfo> treeIO_;

  const oistapp::OISTReadHitTree* readDatafile_;

};

} /* namespace oistapp */

#endif /* OISTAPP_OISTWriteComptonEventTree_H */
