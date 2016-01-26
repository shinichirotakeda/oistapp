%module oISTapp
%{

#include "OISTPrimaryGen2DPhantom.hh"
#include "OISTDetectorImage.hh"
#include "class_list_anlGeant4.hh"
#include "class_list_comptonSoft.hh"

%}

%import "ANL.i"
%import "anlGeant4.i"
%import "comptonSoft.i"

namespace oistapp {


  class OISTPrimaryGen2DPhantom : public anlgeant4::BasicPrimaryGen
  {
  public:
    OISTPrimaryGen2DPhantom();
  };

  class OISTDetectorImage : public comptonsoft::VCSModule
  {

  public:
    OISTDetectorImage();  
  };
  
}

