cmake_minimum_required(VERSION 3.21)

# Find libusb variants
include(${PROJECT_SOURCE_DIR}/cmake/configure-libusb.cmake)

# Configure library
macro(configure_pafe_common target_name)
    target_sources(${target_name} PRIVATE
        felica_command.c
        pasori_command.c
    )
    target_include_directories(${target_name} PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${LIBUSB_INCLUDE_DIR}
    )
    target_compile_definitions(${target_name} PRIVATE
        ${LIBUSB_CAPABILITY}
    )
    target_compile_options(${target_name} PRIVATE
        -Wall
        -Wno-unused-variable
    )
    target_link_libraries(${target_name} PUBLIC
        ${LIBUSB_LIBRARY}
    )
    set_target_properties(${target_name} PROPERTIES
        OUTPUT_NAME pafe
    )
endmacro()

add_library(pafe_static STATIC)
configure_pafe_common(pafe_static)

if(LIBPAFE_BUILD_SHARED_LIBS)
    message(NOTICE "Build shared library too")
    add_library(pafe_shared SHARED)
    configure_pafe_common(pafe_shared)
endif()
