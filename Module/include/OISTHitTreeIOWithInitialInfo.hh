#ifndef OISTAPP_OISTHitTreeIOWithInitialInfo_H
#define OISTAPP_OISTHitTreeIOWithInitialInfo_H 1

#include "OISTHitTreeIO.hh"
#include "InitialInfoTreeIO.hh"

namespace oistapp {

/**
 * 
 * @author Hirokazu Odaka
 * @date 2014-12-02
 */
  class OISTHitTreeIOWithInitialInfo : public OISTHitTreeIO, public comptonsoft::InitialInfoTreeIO
{
public:
  OISTHitTreeIOWithInitialInfo() = default;
  ~OISTHitTreeIOWithInitialInfo();

  void setTree(TTree* tree);
  void defineBranches();
  void setBranchAddresses();
};

} /* namespace oistapp */

#endif /* OISTAPP_OISTHitTreeIOWithInitialInfo_H */
