# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.12.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.12.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/takeda/soft/oistapp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/takeda/soft/oistapp/build2018.10.18

# Utility rule file for oISTapp_swig_compilation.

# Include the progress variables for this target.
include ruby/CMakeFiles/oISTapp_swig_compilation.dir/progress.make

ruby/CMakeFiles/oISTapp_swig_compilation: ruby/CMakeFiles/oISTapp.dir/oISTappRUBY.stamp


ruby/CMakeFiles/oISTapp.dir/oISTappRUBY.stamp: ../ruby/oISTapp.i
ruby/CMakeFiles/oISTapp.dir/oISTappRUBY.stamp: ../ruby/oISTapp.i
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/takeda/soft/oistapp/build2018.10.18/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Swig source"
	cd /Users/takeda/soft/oistapp/build2018.10.18/ruby && /usr/local/Cellar/cmake/3.12.1/bin/cmake -E make_directory /Users/takeda/soft/oistapp/build2018.10.18/ruby /Users/takeda/soft/oistapp/build2018.10.18/ruby/CMakeFiles/oISTapp.dir
	cd /Users/takeda/soft/oistapp/build2018.10.18/ruby && /usr/local/Cellar/cmake/3.12.1/bin/cmake -E touch /Users/takeda/soft/oistapp/build2018.10.18/ruby/CMakeFiles/oISTapp.dir/oISTappRUBY.stamp
	cd /Users/takeda/soft/oistapp/build2018.10.18/ruby && /usr/local/Cellar/cmake/3.12.1/bin/cmake -E env SWIG_LIB=/usr/local/Cellar/swig/3.0.12/share/swig/3.0.12 /usr/local/bin/swig -ruby -outdir /Users/takeda/soft/oistapp/build2018.10.18/ruby -c++ -I/Users/takeda/soft/oistapp/include -I/Users/takeda/include/anlgeant4 -I/Users/takeda/include/anl -I/usr/local/geant4/geant4.10.01.p02-install/include/Geant4 -I/usr/local/include -I/usr/local/lib/QtCore.framework -I/usr/local/lib/QtCore.framework/Headers -I/usr/local/include/QtGui -I/usr/local/include/QtOpenGL -I/usr/local/Cellar/root/6.14.02/include/root -I/Users/takeda/include/comptonsoft -I/Users/takeda/soft/oistapp/PrimaryGen/include -I/Users/takeda/soft/oistapp/Module/include -I/Users/takeda/include/comptonsoft/ruby -I/Users/takeda/include/anlgeant4/ruby -I/Users/takeda/include/anl/ruby -I/Users/takeda/.rbenv/versions/2.4.1/include/ruby-2.4.0 -I/Users/takeda/.rbenv/versions/2.4.1/include/ruby-2.4.0/x86_64-darwin17 -o /Users/takeda/soft/oistapp/build2018.10.18/ruby/CMakeFiles/oISTapp.dir/oISTappRUBY_wrap.cxx /Users/takeda/soft/oistapp/ruby/oISTapp.i

oISTapp_swig_compilation: ruby/CMakeFiles/oISTapp_swig_compilation
oISTapp_swig_compilation: ruby/CMakeFiles/oISTapp.dir/oISTappRUBY.stamp
oISTapp_swig_compilation: ruby/CMakeFiles/oISTapp_swig_compilation.dir/build.make

.PHONY : oISTapp_swig_compilation

# Rule to build all files generated by this target.
ruby/CMakeFiles/oISTapp_swig_compilation.dir/build: oISTapp_swig_compilation

.PHONY : ruby/CMakeFiles/oISTapp_swig_compilation.dir/build

ruby/CMakeFiles/oISTapp_swig_compilation.dir/clean:
	cd /Users/takeda/soft/oistapp/build2018.10.18/ruby && $(CMAKE_COMMAND) -P CMakeFiles/oISTapp_swig_compilation.dir/cmake_clean.cmake
.PHONY : ruby/CMakeFiles/oISTapp_swig_compilation.dir/clean

ruby/CMakeFiles/oISTapp_swig_compilation.dir/depend:
	cd /Users/takeda/soft/oistapp/build2018.10.18 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/takeda/soft/oistapp /Users/takeda/soft/oistapp/ruby /Users/takeda/soft/oistapp/build2018.10.18 /Users/takeda/soft/oistapp/build2018.10.18/ruby /Users/takeda/soft/oistapp/build2018.10.18/ruby/CMakeFiles/oISTapp_swig_compilation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ruby/CMakeFiles/oISTapp_swig_compilation.dir/depend
