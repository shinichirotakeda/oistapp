# Install script for directory: /Users/takeda/soft/oistapp/ruby

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/takeda")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/takeda/lib/ruby/oISTapp.bundle")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/takeda/lib/ruby" TYPE MODULE FILES "/Users/takeda/soft/oistapp/build2018.10.18/ruby/oISTapp.bundle")
  if(EXISTS "$ENV{DESTDIR}/Users/takeda/lib/ruby/oISTapp.bundle" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/takeda/lib/ruby/oISTapp.bundle")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "/Users/takeda/soft/oistapp/build2018.10.18/libOISTapp.dylib" "libOISTapp.dylib"
      "$ENV{DESTDIR}/Users/takeda/lib/ruby/oISTapp.bundle")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/takeda/lib"
      "$ENV{DESTDIR}/Users/takeda/lib/ruby/oISTapp.bundle")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/usr/local/Cellar/root/6.14.02/lib/root"
      "$ENV{DESTDIR}/Users/takeda/lib/ruby/oISTapp.bundle")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/takeda/lib/ruby/oISTapp.bundle")
    endif()
  endif()
endif()

