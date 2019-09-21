cmake_minimum_required(VERSION 3.9)

project(libAudio VERSION 1.0.1 DESCRIPTION "libAudio offers AudioDevice and PortAudioDevice implementation")

set(COMPILER_FLAGS "-std=c++17")

include(GNUInstallDirs)
add_library(libAudio SHARED
        libAudio/AudioDevice.cpp
        libAudio/Frame.cpp
        libAudio/PortAudioDevice.cpp
        )

target_link_libraries(libAudio libDSP)


target_link_libraries(libAudio portaudio)

set_target_properties(libAudio PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER libAudio/libAudio.h)

configure_file(libAudio.pc.in libAudio.pc @ONLY)

target_include_directories(libAudio PRIVATE .)

install(TARGETS libAudio
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/libAudio.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)