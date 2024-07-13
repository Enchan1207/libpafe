#
# libpafe - FeliCa reader handling
#
cmake_minimum_required(VERSION 3.21)

# Project configuration
project(libpafe
    VERSION 0.1.0
    DESCRIPTION "FeliCa reader handling library"
    LANGUAGES C
)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# subdirs
add_subdirectory(src)

option(LIBPAFE_BUILD_SAMPLES "Build sample programs" OFF)
option(LIBPAFE_FORCE_LIBUSB1 "Force to use libusb 1.0" ON)

if(LIBPAFE_BUILD_SAMPLES)
    message(NOTICE "Build samples")
    add_subdirectory(tests)
endif()
