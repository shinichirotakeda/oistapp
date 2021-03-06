cmake_minimum_required(VERSION 2.8)

### Initial definition of cmake variables
set(CMAKE_INSTALL_PREFIX $ENV{HOME} CACHE PATH "install prefix")
set(CMAKE_BUILD_TYPE Release CACHE STRING "build type")
set(CMAKE_CXX_FLAGS_DEBUG "-g -W -Wall" CACHE STRING "CXX_FLAGS for debug")
set(CMAKE_C_FLAGS_DEBUG "-g -W -Wall" CACHE STRING "C_FLAGS for debug")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -W -Wall" CACHE STRING "CXX_FLAGS for release")
set(CMAKE_C_FLAGS_RELEASE "-O2 -W -Wall" CACHE STRING "C_FLAGS for release")

project(OISTapp)
add_definitions("-std=c++11")
set(TARGET_LIBRARY OISTapp)
set(G4_LIB_DIR $ENV{G4_LIB_DIR})

### option ####

option(USE_ROOT "enable ROOT analysis framework" ON)
option(CS_USE_ROOT "enable ROOT analysis framework" ON)
option(USE_RUBY "enable Ruby binding" ON)


### ROOT ###
if(USE_ROOT)
  set(ROOTSYS $ENV{ROOTSYS})
  set(ROOTDIR "/root")
  set(ROOT_INC_DIR ${ROOTSYS}/include${ROOTDIR})
  set(ROOT_LIB_DIR ${ROOTSYS}/lib${ROOTDIR})
  set(ROOT_LIB
    Core RIO Net Hist Graf Graf3d Gpad Tree
    Rint Postscript Matrix Physics MathCore Thread)
  add_definitions(-DUSE_ROOT)
  add_definitions(-DCS_BASIC2)
  message("-- ROOTSYS = ${ROOTSYS}")
endif(USE_ROOT)


if(NOT DEFINED CS_INSTALL)
  if($ENV{CS_INSTALL})
    set(CS_INSTALL $ENV{CS_INSTALL})
  else($ENV{CS_INSTALL})
    set(CS_INSTALL $ENV{HOME})
  endif($ENV{CS_INSTALL})
endif(NOT DEFINED CS_INSTALL)

set(CMAKE_MODULE_PATH ${CS_INSTALL}/lib/comptonsoft ${CMAKE_MODULE_PATH})
include(UseComptonSoft)

message("-- Install destination prefix: ${CMAKE_INSTALL_PREFIX}")

message("--- ANLG4_INC_DIR ${ANLG4_INC_DIR}")
message("--- ANLNEXT_INC_DIR ${ANLNEXT_INC_DIR}")
message("--- G4_INC_DIR ${G4_INC_DIR}")
message("--- CLHEP_INC_DIR ${CLHEP_INC_DIR}")
message("--- BOOST_INC_DIR ${BOOST_INC_DIR}")
message("--- CS_INC_DIR ${CS_INC_DIR}")
message("--- ROOT_INC_DIR ${ROOT_INC_DIR}")


add_definitions(-DANL_USE_HEPVECTOR)
include_directories(include
  ${ANLG4_INC_DIR}
  ${ANLNEXT_INC_DIR}
  ${G4_INC_DIR}
  ${ROOT_INC_DIR}
  ${CS_INC_DIR}
  PrimaryGen/include
  Module/include
  )


message("--- CS_LIB_DIR ${CS_LIB_DIR}")
message("--- ANLG4_LIB_DIR ${ANLG4_LIB_DIR}")
message("--- ANLNEXT_LIB_DIR ${ANLNEXT_LIB_DIR}")
message("--- G4_LIB_DIR ${G4_LIB_DIR}")
message("--- CLHEP_LIB_DIR ${CLHEP_LIB_DIR}")
message("--- ROOT_LIB_DIR ${ROOT_LIB_DIR}")



link_directories(
  ${ANLG4_LIB_DIR}
  ${ANLNEXT_LIB_DIR}
  ${G4_LIB_DIR}
  ${ROOT_LIB_DIR}
  ${CS_LIB_DIR}
  )

add_library(${TARGET_LIBRARY} SHARED
  PrimaryGen/src/OISTPrimaryGen2DPhantom.cc
  PrimaryGen/src/OISTPrimaryGen3DPhantom.cc
  PrimaryGen/src/OISTPrimaryGenUltraMicroPhantom.cc
  Module/src/OISTDetectorImage.cc
  Module/src/OISTDetectorImage_OISTCdTe.cc
  Module/src/OISTReadDataFile_NT.cc
  Module/src/OISTReadDataFile_Muon.cc
  Module/src/OISTReadDataFile_Muon2.cc		
  Module/src/OISTReadDataFile_COMP.cc
  Module/src/OIST1DHistogram.cc
  Module/src/OISTMakeDetectorHits
  Module/src/OISTMakeDetectorHits_OISTCdTe
  Module/src/OISTMakeDetectorHits_Muon
  Module/src/OISTHitTreeIO.cc
  Module/src/OISTHitTreeIOWithInitialInfo.cc
  Module/src/OISTMakeDetectorHits_COMP.cc
  Module/src/OISTWriteHitTree.cc
  Module/src/OISTComptonEventTreeIO.cc
  Module/src/OISTComptonEventTreeIOWithInitialInfo.cc
  Module/src/OISTReadHitTree.cc
  Module/src/OISTWriteComptonEventTree.cc
)

message("--- ANLG4_LIB ${ANLG4_LIB}")
message("--- ANLNEXT_LIB ${ANLNEXT_LIB}")
message("--- CLHEP_LIB ${CLHEP_LIB}")
message("--- CS_LIB ${CS_LIB}")
message("--- ROOT_LIB ${ROOT_LIB}")
message("--- BOOST_LIB ${BOOST_LIB}")

target_link_libraries(${TARGET_LIBRARY}
  ${ANLG4_LIB} ${ANLNEXT_LIB} ${G4_LIB} ${ROOT_LIB} ${CS_LIB} ${BOOST_LIB})

install(TARGETS ${TARGET_LIBRARY}
  LIBRARY
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if(USE_RUBY)
  add_subdirectory(ruby)
endif(USE_RUBY)


