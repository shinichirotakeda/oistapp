#include "OISTWriteHitTree.hh"
#include "TTree.h"
#include "InitialInformation.hh"
#include "DetectorHit.hh"
#include "OISTHitTreeIOWithInitialInfo.hh"
#include "CSHitCollection.hh"

using namespace anl;

namespace oistapp
{

OISTWriteHitTree::OISTWriteHitTree()
  : hitCollection_(nullptr),
    initialInfo_(nullptr),
    hittree_(nullptr),
    treeIO_(new OISTHitTreeIOWithInitialInfo)
{
}

ANLStatus OISTWriteHitTree::mod_his()
{

  GetANLModule("OISTReadDataFile", &readDatafile_);
  VCSModule::mod_his();
  hittree_ = new TTree("hittree", "hittree");
  treeIO_->setTree(hittree_);
  treeIO_->defineBranches();

  return AS_OK;
}

ANLStatus OISTWriteHitTree::mod_init()
{
  VCSModule::mod_init();

  GetANLModule("CSHitCollection", &hitCollection_);
  EvsDef("WriteHitTree:Fill");

  if (ModuleExist("InitialInformation")) {
    GetANLModuleIF("InitialInformation", &initialInfo_);
    treeIO_->enableInitialInfoRecord();
  }
  else {
    treeIO_->disableInitialInfoRecord();
  }
  
  return AS_OK;
}

ANLStatus OISTWriteHitTree::mod_ana()
{
  int64_t eventID = -1;

  exptime = readDatafile_->getExpTime();
  
  if (initialInfo_) {
    eventID = initialInfo_->EventID();
    treeIO_->setInitialInfo(initialInfo_->InitialEnergy(),
                            initialInfo_->InitialDirection(),
                            initialInfo_->InitialTime(),
                            initialInfo_->InitialPosition(),
                            initialInfo_->InitialPolarization());
    treeIO_->setWeight(initialInfo_->Weight());
  }
  else {
    eventID = get_event_loop_index();
  }
  
  const int NumTimeGroups = hitCollection_->NumberOfTimeGroups();
  for (int timeGroup=0; timeGroup<NumTimeGroups; timeGroup++) {
    const std::vector<comptonsoft::DetectorHit_sptr>& hits
      = hitCollection_->getHits(timeGroup);
    if (hits.size() > 0) {
      treeIO_->fillHits(eventID, exptime, hits);
      EvsSet("WriteHitTree:Fill");
    }
  }

  return AS_OK;
}

} /* namespace oistapp */
