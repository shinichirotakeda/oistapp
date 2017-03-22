#include "OISTWriteComptonEventTree.hh"
#include "TTree.h"
#include "InitialInformation.hh"
#include "BasicComptonEvent.hh"
#include "OISTComptonEventTreeIOWithInitialInfo.hh"
#include "EventReconstruction.hh"

using namespace anl;

namespace oistapp
{

OISTWriteComptonEventTree::OISTWriteComptonEventTree()
  : cetree_(nullptr),
    eventReconstruction_(nullptr),
    initialInfo_(nullptr),
    treeIO_(new OISTComptonEventTreeIOWithInitialInfo)
{
}

OISTWriteComptonEventTree::~OISTWriteComptonEventTree() = default;

ANLStatus OISTWriteComptonEventTree::mod_startup()
{
  return AS_OK;
}

ANLStatus OISTWriteComptonEventTree::mod_his()
{

  GetANLModule("OISTReadHitTree", &readDatafile_);
  VCSModule::mod_his();

  cetree_ = new TTree("cetree", "cetree");
  treeIO_->setTree(cetree_);
  treeIO_->defineBranches();

  return AS_OK;
}

ANLStatus OISTWriteComptonEventTree::mod_init()
{
  GetANLModuleNC("EventReconstruction", &eventReconstruction_);

  if (ModuleExist("InitialInformation")) {
    GetANLModuleIF("InitialInformation", &initialInfo_);
    treeIO_->enableInitialInfoRecord();
  }
  else {
    treeIO_->disableInitialInfoRecord();
  }

  return AS_OK;
}

ANLStatus OISTWriteComptonEventTree::mod_ana()
{
  int64_t eventID = -1;
  
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
  
  const BasicComptonEvent& event
    = eventReconstruction_->getComptonEvent();
  treeIO_->fillEvent(eventID, readDatafile_->getExpTime(),event);

  return AS_OK;
}

} /* namespace oistapp */
