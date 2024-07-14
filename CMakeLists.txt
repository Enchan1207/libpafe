cmake_minimum_required(VERSION 3.21)

project(libpafe
    VERSION 0.1.1
    DESCRIPTION "FeliCa reader handling library"
    LANGUAGES C
)

add_subdirectory(src)

option(LIBPAFE_BUILD_SAMPLES "Build sample programs" OFF)
option(LIBPAFE_BUILD_SHARED_LIBS "Build shared library" ON)

if(LIBPAFE_BUILD_SAMPLES)
    message(NOTICE "Build samples")
    add_subdirectory(tests)
endif()
