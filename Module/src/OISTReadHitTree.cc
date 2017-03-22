#include "OISTReadHitTree.hh"
#include "TChain.h"
#include "DetectorHit.hh"
#include "OISTHitTreeIOWithInitialInfo.hh"
#include "CSHitCollection.hh"

using namespace anl;

namespace oistapp
{

OISTReadHitTree::OISTReadHitTree()
  : anlgeant4::InitialInformation(false),
    hitCollection_(nullptr),
    treeIO_(new OISTHitTreeIOWithInitialInfo)
{
  add_alias("InitialInformation");
}

OISTReadHitTree::~OISTReadHitTree() = default;

ANLStatus OISTReadHitTree::mod_startup()
{
  register_parameter(&fileList_, "file_list", "seq", "hittree.root");
  return AS_OK;
}

ANLStatus OISTReadHitTree::mod_init()
{
  VCSModule::mod_init();
  
  GetANLModuleNC("CSHitCollection", &hitCollection_);

  hittree_ = new TChain("hittree");
  for (const std::string& filename: fileList_) {
    hittree_->Add(filename.c_str());
  }

  treeIO_->setTree(hittree_);
  if (hittree_->GetBranch("ini_energy")) {
    setInitialInformationStored();
    treeIO_->enableInitialInfoRecord();
  }
  else {
    treeIO_->disableInitialInfoRecord();
  }
  treeIO_->setBranchAddresses();

  numEntries_ = hittree_->GetEntries();
  std::cout << "Number of entries: " << numEntries_ << std::endl;

  return AS_OK;
}

ANLStatus OISTReadHitTree::mod_ana()
{
  if (entryIndex_ == numEntries_) {
    return AS_QUIT;
  }

  hittree_->GetEntry(entryIndex_);
  exptime_ = treeIO_->getExpTime();
  
  const int64_t EventID = treeIO_->getEventID();
  setEventID(EventID);

  if (InitialInformationStored()) {
    setInitialEnergy(treeIO_->getInitialEnergy());
    setInitialDirection(treeIO_->getInitialDirection());
    setInitialTime(treeIO_->getInitialTime());
    setInitialPosition(treeIO_->getInitialPosition());
    setInitialPolarization(treeIO_->getInitialPolarization());
  }
  
  if (WeightStored()) {
    setWeight(treeIO_->getWeight());
  }

  std::vector<DetectorHit_sptr> hits = treeIO_->retrieveHits(entryIndex_, false);

  
  for (auto& hit: hits) {
    insertHit(hit);
  }
  
  return AS_OK;
}

void OISTReadHitTree::insertHit(const DetectorHit_sptr& hit)
{
  hitCollection_->insertHit(hit);
}

} /* namespace oistapp */
