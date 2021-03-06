cmake_minimum_required(VERSION 3.9)

project(libDSP VERSION 1.0.1 DESCRIPTION "libDSP offers tick based signal processing classes")

include(GNUInstallDirs)

add_library(libDSP SHARED
        libDSP/src/DSPHost.cpp
        libDSP/src/DSPNodes/DSPContainer.cpp
        libDSP/src/DSPNodes/DSPInputNode.cpp
        libDSP/src/DSPNodes/DSPNode.cpp
        libDSP/src/DSPNodes/DSPOutputNode.cpp
        libDSP/src/misc/Countdown.cpp
        libDSP/src/misc/RingBuffer.cpp
        libDSP/src/Modules/DSPModule.cpp
        libDSP/src/Modules/Parameter.cpp
        libDSP/src/UUID/UUID.cpp
        libDSP/src/plugin/PluginLoader.cpp
        )

OPTION(BUILD_TESTS "Enable building of the unit testsuit" ON)

target_link_libraries(libDSP uuid)
target_link_libraries(libDSP libFilesystem)

set_target_properties(libDSP PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER libDSP/include/libDSP.h)

set(COMPILER_FLAGS "-std=c++17")

configure_file(libDSP.pc.in libDSP.pc @ONLY)

target_include_directories(libDSP PUBLIC .)


if(BUILD_TESTS)
    project(catch2 CXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wmaybe-uninitialized -Wuninitialized -Wdouble-promotion -Wreturn-type")
    add_library(catch2 tests/catchwrapper.cpp)
    file(GLOB_RECURSE UNIT_TEST_FILES tests/src/*.cpp)
    list(REMOVE_ITEM UNIT_TEST_FILES EXCLUDE REGEX tests/catchwrapper.cpp)
    add_executable(libDSP-tests ${UNIT_TEST_FILES})
    target_link_libraries(libDSP-tests PUBLIC libDSP)
    target_link_libraries(libDSP-tests PUBLIC catch2)
endif()

install(TARGETS libDSP
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/libDSP.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)