# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.3.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.3.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/takeda/soft/oistapp/PrimaryGen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/takeda/soft/oistapp/PrimaryGen/build

# Include any dependencies generated for this target.
include CMakeFiles/OISTapp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OISTapp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OISTapp.dir/flags.make

CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o: CMakeFiles/OISTapp.dir/flags.make
CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o: ../src/OISTPrimaryGen2DPhantom.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/takeda/soft/oistapp/PrimaryGen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o -c /Users/takeda/soft/oistapp/PrimaryGen/src/OISTPrimaryGen2DPhantom.cc

CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/takeda/soft/oistapp/PrimaryGen/src/OISTPrimaryGen2DPhantom.cc > CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.i

CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/takeda/soft/oistapp/PrimaryGen/src/OISTPrimaryGen2DPhantom.cc -o CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.s

CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o.requires:

.PHONY : CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o.requires

CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o.provides: CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o.requires
	$(MAKE) -f CMakeFiles/OISTapp.dir/build.make CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o.provides.build
.PHONY : CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o.provides

CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o.provides.build: CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o


# Object files for target OISTapp
OISTapp_OBJECTS = \
"CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o"

# External object files for target OISTapp
OISTapp_EXTERNAL_OBJECTS =

libOISTapp.dylib: CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o
libOISTapp.dylib: CMakeFiles/OISTapp.dir/build.make
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4Tree.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4GMocren.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4visHepRep.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4RayTracer.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4VRML.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4interfaces.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4persistency.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4analysis.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4error_propagation.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4readout.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4physicslists.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4parmodels.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4FR.dylib
libOISTapp.dylib: /usr/X11R6/lib/libSM.dylib
libOISTapp.dylib: /usr/X11R6/lib/libICE.dylib
libOISTapp.dylib: /usr/X11R6/lib/libX11.dylib
libOISTapp.dylib: /usr/X11R6/lib/libXext.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4vis_management.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4modeling.dylib
libOISTapp.dylib: /usr/local/lib/libxerces-c.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4run.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4event.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4tracking.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4processes.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4zlib.dylib
libOISTapp.dylib: /usr/lib/libexpat.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4digits_hits.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4track.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4particles.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4geometry.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4geomUSolids.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4materials.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4graphics_reps.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4intercoms.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4global.dylib
libOISTapp.dylib: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4clhep.dylib
libOISTapp.dylib: CMakeFiles/OISTapp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/takeda/soft/oistapp/PrimaryGen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libOISTapp.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OISTapp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OISTapp.dir/build: libOISTapp.dylib

.PHONY : CMakeFiles/OISTapp.dir/build

CMakeFiles/OISTapp.dir/requires: CMakeFiles/OISTapp.dir/src/OISTPrimaryGen2DPhantom.cc.o.requires

.PHONY : CMakeFiles/OISTapp.dir/requires

CMakeFiles/OISTapp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OISTapp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OISTapp.dir/clean

CMakeFiles/OISTapp.dir/depend:
	cd /Users/takeda/soft/oistapp/PrimaryGen/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/takeda/soft/oistapp/PrimaryGen /Users/takeda/soft/oistapp/PrimaryGen /Users/takeda/soft/oistapp/PrimaryGen/build /Users/takeda/soft/oistapp/PrimaryGen/build /Users/takeda/soft/oistapp/PrimaryGen/build/CMakeFiles/OISTapp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OISTapp.dir/depend

