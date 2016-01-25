%module oISTapp
%{

#include "OISTPrimaryGen2DPhantom.hh"
#include "class_list_anlGeant4.hh"

%}

%import "anlGeant4.i"

namespace oistapp {


  class OISTPrimaryGen2DPhantom : public anlgeant4::BasicPrimaryGen
  {
  public:
    PrimaryGen2DPhantom() {}
    ~PrimaryGen2DPhantom() {}
  };
  
}

