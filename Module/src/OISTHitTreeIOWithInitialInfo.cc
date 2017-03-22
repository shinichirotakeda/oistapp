#include "OISTHitTreeIOWithInitialInfo.hh"

namespace oistapp
{

OISTHitTreeIOWithInitialInfo::~OISTHitTreeIOWithInitialInfo() = default;

void OISTHitTreeIOWithInitialInfo::setTree(TTree* tree)
{
  OISTHitTreeIO::setTree(tree);
  InitialInfoTreeIO::setTree(tree);
}

void OISTHitTreeIOWithInitialInfo::defineBranches()
{
  OISTHitTreeIO::defineBranches();
  InitialInfoTreeIO::defineBranches();
}

void OISTHitTreeIOWithInitialInfo::setBranchAddresses()
{
  OISTHitTreeIO::setBranchAddresses();
  InitialInfoTreeIO::setBranchAddresses();
}

} /* namespace oistapp */
