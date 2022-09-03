cmake_minimum_required( VERSION 3.10 )
project( rbs )

add_library( rbs INTERFACE )
add_library( rbs::rbs ALIAS rbs )

target_include_directories(
    rbs

    INTERFACE

        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_compile_features(
    rbs

    INTERFACE

        cxx_std_17
)

enable_testing()
add_subdirectory( test )