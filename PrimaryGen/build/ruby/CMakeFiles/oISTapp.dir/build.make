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
include ruby/CMakeFiles/oISTapp.dir/depend.make

# Include the progress variables for this target.
include ruby/CMakeFiles/oISTapp.dir/progress.make

# Include the compile flags for this target's objects.
include ruby/CMakeFiles/oISTapp.dir/flags.make

ruby/oISTappRUBY_wrap.cxx: ../ruby/oISTapp.i
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/takeda/soft/oistapp/PrimaryGen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Swig source"
	cd /Users/takeda/soft/oistapp/PrimaryGen/build/ruby && /usr/local/Cellar/cmake/3.3.2/bin/cmake -E make_directory /Users/takeda/soft/oistapp/PrimaryGen/build/ruby
	cd /Users/takeda/soft/oistapp/PrimaryGen/build/ruby && /usr/local/bin/swig -ruby -outdir /Users/takeda/soft/oistapp/PrimaryGen/build/ruby -c++ -I/Users/takeda/soft/oistapp/PrimaryGen/include -I/Users/takeda/include/anlgeant4 -I/Users/takeda/include/anl -I/usr/local/geant4/geant4.10.01.p02-install/include/Geant4 -I/usr/local/include -I/usr/local/Cellar/qt/4.8.7_1/include -I/usr/local/Cellar/qt/4.8.7_1/lib/QtCore.framework -I/usr/local/Cellar/qt/4.8.7_1/lib/QtCore.framework/Headers -I/usr/local/Cellar/qt/4.8.7_1/include/QtGui -I/usr/local/Cellar/qt/4.8.7_1/include/QtOpenGL -I/usr/local/root-5.34.34/include -I/Users/takeda/include/anlgeant4/ruby -I/Users/takeda/include/anl/ruby -I/Users/takeda/.rbenv/versions/2.2.3/include/ruby-2.2.0 -I/Users/takeda/.rbenv/versions/2.2.3/include/ruby-2.2.0/x86_64-darwin15 -o /Users/takeda/soft/oistapp/PrimaryGen/build/ruby/oISTappRUBY_wrap.cxx /Users/takeda/soft/oistapp/PrimaryGen/ruby/oISTapp.i

ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o: ruby/CMakeFiles/oISTapp.dir/flags.make
ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o: ruby/oISTappRUBY_wrap.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/takeda/soft/oistapp/PrimaryGen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o"
	cd /Users/takeda/soft/oistapp/PrimaryGen/build/ruby && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o -c /Users/takeda/soft/oistapp/PrimaryGen/build/ruby/oISTappRUBY_wrap.cxx

ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.i"
	cd /Users/takeda/soft/oistapp/PrimaryGen/build/ruby && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/takeda/soft/oistapp/PrimaryGen/build/ruby/oISTappRUBY_wrap.cxx > CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.i

ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.s"
	cd /Users/takeda/soft/oistapp/PrimaryGen/build/ruby && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/takeda/soft/oistapp/PrimaryGen/build/ruby/oISTappRUBY_wrap.cxx -o CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.s

ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o.requires:

.PHONY : ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o.requires

ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o.provides: ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o.requires
	$(MAKE) -f ruby/CMakeFiles/oISTapp.dir/build.make ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o.provides.build
.PHONY : ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o.provides

ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o.provides.build: ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o


# Object files for target oISTapp
oISTapp_OBJECTS = \
"CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o"

# External object files for target oISTapp
oISTapp_EXTERNAL_OBJECTS =

ruby/oISTapp.bundle: ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o
ruby/oISTapp.bundle: ruby/CMakeFiles/oISTapp.dir/build.make
ruby/oISTapp.bundle: libOISTapp.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4Tree.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4GMocren.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4visHepRep.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4RayTracer.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4VRML.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4interfaces.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4persistency.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4analysis.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4error_propagation.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4readout.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4physicslists.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4parmodels.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4FR.dylib
ruby/oISTapp.bundle: /usr/X11R6/lib/libSM.dylib
ruby/oISTapp.bundle: /usr/X11R6/lib/libICE.dylib
ruby/oISTapp.bundle: /usr/X11R6/lib/libX11.dylib
ruby/oISTapp.bundle: /usr/X11R6/lib/libXext.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4vis_management.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4modeling.dylib
ruby/oISTapp.bundle: /usr/local/lib/libxerces-c.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4run.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4event.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4tracking.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4processes.dylib
ruby/oISTapp.bundle: /usr/lib/libexpat.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4digits_hits.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4track.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4particles.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4geometry.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4materials.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4graphics_reps.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4intercoms.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4global.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4clhep.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4zlib.dylib
ruby/oISTapp.bundle: /usr/local/geant4/geant4.10.01.p02-install/lib/libG4geomUSolids.dylib
ruby/oISTapp.bundle: ruby/CMakeFiles/oISTapp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/takeda/soft/oistapp/PrimaryGen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared module oISTapp.bundle"
	cd /Users/takeda/soft/oistapp/PrimaryGen/build/ruby && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/oISTapp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ruby/CMakeFiles/oISTapp.dir/build: ruby/oISTapp.bundle

.PHONY : ruby/CMakeFiles/oISTapp.dir/build

ruby/CMakeFiles/oISTapp.dir/requires: ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx.o.requires

.PHONY : ruby/CMakeFiles/oISTapp.dir/requires

ruby/CMakeFiles/oISTapp.dir/clean:
	cd /Users/takeda/soft/oistapp/PrimaryGen/build/ruby && $(CMAKE_COMMAND) -P CMakeFiles/oISTapp.dir/cmake_clean.cmake
.PHONY : ruby/CMakeFiles/oISTapp.dir/clean

ruby/CMakeFiles/oISTapp.dir/depend: ruby/oISTappRUBY_wrap.cxx
	cd /Users/takeda/soft/oistapp/PrimaryGen/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/takeda/soft/oistapp/PrimaryGen /Users/takeda/soft/oistapp/PrimaryGen/ruby /Users/takeda/soft/oistapp/PrimaryGen/build /Users/takeda/soft/oistapp/PrimaryGen/build/ruby /Users/takeda/soft/oistapp/PrimaryGen/build/ruby/CMakeFiles/oISTapp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ruby/CMakeFiles/oISTapp.dir/depend

