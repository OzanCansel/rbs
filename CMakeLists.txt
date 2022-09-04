cmake_minimum_required( VERSION 3.10 )
project( rbs )

add_library( rbs INTERFACE )
add_library( rbs::rbs ALIAS rbs )

target_include_directories(
    rbs

    INTERFACE

        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:src>
)

target_compile_features(
    rbs

    INTERFACE

        cxx_std_17
)

include( GNUInstallDirs )

install(
    TARGETS rbs
    EXPORT rbs-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/rbs
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

include( CMakePackageConfigHelpers )

install(
    EXPORT rbs-targets
    FILE rbs-targets.cmake
    NAMESPACE rbs::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rbs
)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/rbs-config.cmake.in
    ${CMAKE_BINARY_DIR}/cmake/rbs-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rbs
)

write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/rbs-config-version.cmake
    VERSION 3.1
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
    ${CMAKE_BINARY_DIR}/cmake/rbs-config.cmake
    ${CMAKE_BINARY_DIR}/cmake/rbs-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rbs
)

export( EXPORT rbs-targets
    FILE ${CMAKE_BINARY_DIR}/cmake/rbs-targets.cmake
    NAMESPACE rbs::
)

add_subdirectory( example )
enable_testing()
add_subdirectory( test )