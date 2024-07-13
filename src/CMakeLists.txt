cmake_minimum_required(VERSION 3.21)

# Find libusb variants
include(${PROJECT_SOURCE_DIR}/cmake/configure-libusb.cmake)

# Configure library
add_library(pafe)
target_sources(pafe PRIVATE
    felica_command.c
    pasori_command.c
)
target_include_directories(pafe PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${LIBUSB_INCLUDE_DIR}
)
target_compile_definitions(pafe PRIVATE
    ${LIBUSB_CAPABILITY}
)
target_compile_options(pafe PRIVATE
    -Wall
)
target_link_libraries(pafe PUBLIC
    ${LIBUSB_LIBRARY}
)
