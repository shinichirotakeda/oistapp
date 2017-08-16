%module oISTapp
%{

#include "OISTPrimaryGen2DPhantom.hh"
#include "OISTPrimaryGenUltraMicroPhantom.hh"
#include "OISTDetectorImage.hh"
#include "OISTDetectorImage_OISTCdTe.hh"
#include "OISTReadDataFile_NT.hh"
#include "OISTReadDataFile_Muon.hh"
#include "OISTReadDataFile_Muon2.hh"
#include "OIST1DHistogram.hh"
#include "OISTMakeDetectorHits.hh"
#include "OISTMakeDetectorHits_OISTCdTe.hh"
#include "OISTMakeDetectorHits_Muon.hh"
#include "OISTHitTreeIO.hh"
#include "OISTHitTreeIOWithInitialInfo.hh"
#include "OISTMakeDetectorHits_COMP.hh"
#include "OISTReadDataFile_COMP.hh"
#include "OISTWriteHitTree.hh"
#include "OISTComptonEventTreeIO.hh"
#include "OISTComptonEventTreeIOWithInitialInfo.hh"
#include "OISTReadHitTree.hh"
#include "OISTWriteComptonEventTree.hh"  
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

  class OISTPrimaryGenUltraMicroPhantom : public anlgeant4::BasicPrimaryGen
  {
  public:
    OISTPrimaryGenUltraMicroPhantom();
  };
  
  class OISTDetectorImage : public comptonsoft::VCSModule
  {

  public:
    OISTDetectorImage();  
  };

  class OISTDetectorImage_OISTCdTe : public comptonsoft::VCSModule
  {

  public:
    OISTDetectorImage_OISTCdTe();  
  };
  
  class OISTReadDataFile_NT : public comptonsoft::ReadDataFile
  {

  public:
    OISTReadDataFile_NT ();  
  };

  class OISTReadDataFile_Muon : public comptonsoft::ReadDataFile
  {

  public:
    OISTReadDataFile_Muon ();  
  };

  class OISTReadDataFile_Muon2 : public comptonsoft::ReadDataFile
  {

  public:
    OISTReadDataFile_Muon2 ();  
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

  class OISTMakeDetectorHits_OISTCdTe : public comptonsoft::SelectHits
  {

  public:
    OISTMakeDetectorHits_OISTCdTe ();  
  };
  
  class OISTMakeDetectorHits_Muon : public comptonsoft::SelectHits
  {

  public:
    OISTMakeDetectorHits_Muon ();
  };

  class OISTHitTreeIO
  {

  public:
    OISTHitTreeIO ();
  };

  class OISTHitTreeIOWithInitialInfo : public oistapp::OISTHitTreeIO, public comptonsoft::InitialInfoTreeIO
  {
    public:
    OISTHitTreeIOWithInitialInfo ();
  };

  class OISTMakeDetectorHits_COMP : public comptonsoft::SelectHits
  {
    public:
    OISTMakeDetectorHits_COMP ();
  };

  class OISTReadDataFile_COMP : public comptonsoft::ReadDataFile
  {
  public:
    OISTReadDataFile_COMP ();
  };
  
  class OISTWriteHitTree : public comptonsoft::VCSModule
  {
  public:
    OISTWriteHitTree ();
  };


  class OISTComptonEventTreeIO
  {
  public:
    OISTComptonEventTreeIO();
  };

  class OISTComptonEventTreeIOWithInitialInfo : public oistapp::OISTComptonEventTreeIO, public comptonsoft::InitialInfoTreeIO
  {
  public:
    OISTComptonEventTreeIOWithInitialInfo();
  };

  class OISTReadHitTree : public comptonsoft::VCSModule, public anlgeant4::InitialInformation
  {
  public:
    OISTReadHitTree();
  };

  class OISTWriteComptonEventTree : public comptonsoft::VCSModule
  {
  public:
    OISTWriteComptonEventTree();
  };
  
}

