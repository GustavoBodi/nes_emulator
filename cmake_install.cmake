# Install script for directory: /home/gustavo/programming/nes_emulator

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Nes" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Nes")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Nes"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/gustavo/programming/nes_emulator/Nes")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Nes" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Nes")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Nes"
         OLD_RPATH "/home/gustavo/.conan2/p/b/sdl52238bc7b3ffd/p/lib:/home/gustavo/.conan2/p/b/libic84528691b8686/p/lib:/home/gustavo/.conan2/p/b/libald5946b0b396c8/p/lib:/home/gustavo/.conan2/p/b/pulse00bacc08d57d6/p/lib:/home/gustavo/.conan2/p/b/pulse00bacc08d57d6/p/lib/pulseaudio:/home/gustavo/.conan2/p/b/libsn502b35b9d55ae/p/lib:/home/gustavo/.conan2/p/b/oggdc4ab97d6d4e8/p/lib:/home/gustavo/.conan2/p/b/vorbi2ba819d9afb8b/p/lib:/home/gustavo/.conan2/p/b/flac3fd4669042a57/p/lib:/home/gustavo/.conan2/p/b/opusb420565ed11df/p/lib:/home/gustavo/.conan2/p/b/mpg127c9b5c804ab21/p/lib:/home/gustavo/.conan2/p/b/libmp402d0e72a4a02/p/lib:/home/gustavo/.conan2/p/b/libcace426301bbe37/p/lib:/home/gustavo/.conan2/p/b/libto4f2bdb10a37bd/p/lib:/home/gustavo/.conan2/p/b/opens554f89525d13f/p/lib:/home/gustavo/.conan2/p/b/zlibebce7ed3d7620/p/lib:/home/gustavo/.conan2/p/b/wayla6fbb5649a95f1/p/lib:/home/gustavo/.conan2/p/b/libff48e19456ad6b8/p/lib:/home/gustavo/.conan2/p/b/expatdd6bf1368eb95/p/lib:/home/gustavo/.conan2/p/b/libxme2ddd747c8af5/p/lib:/home/gustavo/.conan2/p/b/xkbcob6189501ec354/p/lib:/home/gustavo/.conan2/p/b/libun6139c8604a9c3/p/lib:/home/gustavo/.conan2/p/b/xz_ut4dd62a7b15173/p/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/Nes")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/gustavo/programming/nes_emulator/include/")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/gustavo/programming/nes_emulator/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/gustavo/programming/nes_emulator/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
