#include "OISTComptonEventTreeIOWithInitialInfo.hh"

namespace oistapp
{

OISTComptonEventTreeIOWithInitialInfo::~OISTComptonEventTreeIOWithInitialInfo() = default;

void OISTComptonEventTreeIOWithInitialInfo::setTree(TTree* tree)
{
  OISTComptonEventTreeIO::setTree(tree);
  InitialInfoTreeIO::setTree(tree);
}

void OISTComptonEventTreeIOWithInitialInfo::defineBranches()
{
  OISTComptonEventTreeIO::defineBranches();
  InitialInfoTreeIO::defineBranches();
}

void OISTComptonEventTreeIOWithInitialInfo::setBranchAddresses()
{
  OISTComptonEventTreeIO::setBranchAddresses();
  InitialInfoTreeIO::setBranchAddresses();
}

} /* namespace oistapp */
