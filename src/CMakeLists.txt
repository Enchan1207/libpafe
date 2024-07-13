cmake_minimum_required(VERSION 3.21)

# Find libusb 1.0
find_path(LIBUSB_INCLUDE_DIR
    NAMES libusb.h
    PATH_SUFFIXES "libusb-1.0"
)

find_library(LIBUSB_LIBRARY
    NAMES usb-1.0
    REQUIRED
)
message(NOTICE "libusb found")
message(NOTICE ${LIBUSB_INCLUDE_DIR})
message(NOTICE ${LIBUSB_LIBRARY})

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
    HAVE_LIBUSB_1
)
target_compile_options(pafe PRIVATE
    -Wall
)
target_link_libraries(pafe PUBLIC
    ${LIBUSB_LIBRARY}
)
