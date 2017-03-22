#ifndef OISTAPP_OISTComptonEventTreeIOWithInitialInfo_H
#define OISTAPP_OISTComptonEventTreeIOWithInitialInfo_H 1

#include "OISTComptonEventTreeIO.hh"
#include "InitialInfoTreeIO.hh"

namespace oistapp {

/**
 * 
 * @author Hirokazu Odaka
 * @date 2014-12-02
 */
class OISTComptonEventTreeIOWithInitialInfo : public OISTComptonEventTreeIO, public InitialInfoTreeIO
{
public:
  OISTComptonEventTreeIOWithInitialInfo() = default;
  ~OISTComptonEventTreeIOWithInitialInfo();

  void setTree(TTree* tree);
  void defineBranches();
  void setBranchAddresses();
};

} /* namespace oistapp */

#endif /* OISTAPP_OISTComptonEventTreeIOWithInitialInfo_H */
