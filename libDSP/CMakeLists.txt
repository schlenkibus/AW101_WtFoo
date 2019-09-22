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
        libDSP/src/Modules/Input.cpp
        libDSP/src/Modules/Output.cpp
        libDSP/src/Modules/Parameter.cpp
        libDSP/src/UUID/UUID.cpp
        )

target_link_libraries(libDSP uuid)

set_target_properties(libDSP PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER libDSP/include/libDSP.h)

set(COMPILER_FLAGS "-std=c++17")

configure_file(libDSP.pc.in libDSP.pc @ONLY)

target_include_directories(libDSP PUBLIC .)

install(TARGETS libDSP
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/libDSP.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)