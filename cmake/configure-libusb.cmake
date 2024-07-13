#
# Configure libusb
#
cmake_minimum_required(VERSION 3.21)

include(FindPackageHandleStandardArgs)

# Find libusb 0.1
find_path(LIBUSB_0_INCLUDE_DIR NAMES usb.h PATH_SUFFIXES "libusb-0.1")
find_library(LIBUSB_0_LIBRARY NAMES usb)
find_package_handle_standard_args(libusb_0 DEFAULT_MSG LIBUSB_0_LIBRARY LIBUSB_0_INCLUDE_DIR)

if(LIBUSB_0_FOUND)
    set(LIBUSB_INCLUDE_DIR ${LIBUSB_0_INCLUDE_DIR})
    set(LIBUSB_LIBRARY ${LIBUSB_0_LIBRARY})
    set(LIBUSB_CAPABILITY "HAVE_LIBUSB")
endif()

# Find libusb 1.0
find_path(LIBUSB_1_INCLUDE_DIR NAMES libusb.h PATH_SUFFIXES "libusb-1.0")
find_library(LIBUSB_1_LIBRARY NAMES usb-1.0)
find_package_handle_standard_args(libusb_1 DEFAULT_MSG LIBUSB_1_LIBRARY LIBUSB_1_INCLUDE_DIR)

if(LIBUSB_1_FOUND)
    set(LIBUSB_INCLUDE_DIR ${LIBUSB_1_INCLUDE_DIR})
    set(LIBUSB_LIBRARY ${LIBUSB_1_LIBRARY})
    set(LIBUSB_CAPABILITY "HAVE_LIBUSB_1")
endif()

if(LIBPAFE_FORCE_LIBUSB1)
    message(NOTICE "The use of libusb-1.0 has been forced.")

    if(NOT LIBUSB_1_FOUND)
        message(FATAL_ERROR "The use of libusb-1.0 was forced, but it was not found. Please confirm whether it's installed.")
    endif()
endif()
