cmake_minimum_required(VERSION 3.21)

macro(configure_pafe_sample_common target_name)
    target_sources(${target_name} PRIVATE
        ${target_name}.c
    )
    target_include_directories(${target_name} PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    )
    target_link_libraries(${target_name} PUBLIC
        pafe_static
    )
endmacro()

# pasori_test
add_executable(pasori_test)
configure_pafe_sample_common(pasori_test)

# felica_dump
add_executable(felica_dump)
configure_pafe_sample_common(felica_dump)
