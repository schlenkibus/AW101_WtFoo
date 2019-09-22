cmake_minimum_required(VERSION 3.2)

project(libAudio)
set(BUILD_SHARED_LIBS ON)

include(GNUInstallDirs)

file(GLOB_RECURSE HEADER_FILES libAudio/include/*.h)
file(GLOB_RECURSE SOURCE_FILES ./*.cpp)


add_library(libAudio SHARED ${SOURCE_FILES})
find_package(PkgConfig REQUIRED)


target_include_directories(libAudio PUBLIC ${libDSP_INCLUDE_DIRS})
target_link_libraries(libAudio PUBLIC ${libDSP_LIBRARIES})
link_directories(${libDSP_LIBRARY_DIRS})

target_link_libraries(libAudio portaudio)
configure_file(libAudio.pc.in libAudio.pc @ONLY)


target_include_directories(
        libAudio INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/..>)

include_directories(nltools ${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(nltools libAudio/include/)
include_directories(nltools libAudio/src/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wdouble-promotion")

set(headers_install_dir ${CMAKE_INSTALL_INCLUDEDIR}/libAudio)

install(FILES ${HEADER_FILES} DESTINATION ${headers_install_dir})
install(TARGETS libAudio DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${CMAKE_BINARY_DIR}/libDSP.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)