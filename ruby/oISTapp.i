%module oISTapp
%{

#include "OISTPrimaryGen2DPhantom.hh"
#include "OISTDetectorImage.hh"
#include "OISTReadDataFile_NT.hh"
#include "OIST1DHistogram.hh"
#include "OISTMakeDetectorHits.hh"
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

  class OISTReadDataFile_NT : public comptonsoft::ReadDataFile
  {

  public:
    OISTReadDataFile_NT ();  
  };

  class OIST1DHistogram : public comptonsoft::VCSModule
  {

  public:
    OIST1DHistogram ();  
  };

  class OISTMakeDetectorHits : public comptonsoft::SelectHits
  {

  public:
    OISTMakeDetectorHits ();  
  };

  
}

