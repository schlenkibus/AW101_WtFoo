cmake_minimum_required(VERSION 3.9)

project(libDSP VERSION 1.0.1 DESCRIPTION "libDSP offers tick based signal processing classes")

include(GNUInstallDirs)

add_library(libDSP SHARED
        libDSP/DSPHost.cpp
        libDSP/DSPNodes/DSPContainer.cpp
        libDSP/DSPNodes/DSPInputNode.cpp
        libDSP/DSPNodes/DSPNode.cpp
        libDSP/DSPNodes/DSPOutputNode.cpp
        libDSP/misc/Countdown.cpp
        libDSP/misc/RingBuffer.cpp
        libDSP/Modules/DSPModule.cpp
        libDSP/Modules/Input.cpp
        libDSP/Modules/Output.cpp
        libDSP/UUID/UUID.cpp
        )

target_link_libraries(libDSP uuid)

set_target_properties(libDSP PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER libDSP/libDSP.h)

set(COMPILER_FLAGS "-std=c++17")

configure_file(libDSP.pc.in libDSP.pc @ONLY)

target_include_directories(libDSP PRIVATE .)

install(TARGETS libDSP
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/libDSP.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)