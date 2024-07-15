#
# Cmake
#
cmake_minimum_required(VERSION 3.21)

# pasori_test
add_executable(pasori_test)
target_sources(pasori_test PRIVATE
    pasori_test.c
)
target_include_directories(pasori_test PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(pasori_test PUBLIC
    pafe
)

# felica_dump
add_executable(felica_dump)
target_sources(felica_dump PRIVATE
    felica_dump.c
)
target_include_directories(felica_dump PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(felica_dump PUBLIC
    pafe
)
