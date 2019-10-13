cmake_minimum_required(VERSION 3.9)

project(IODevice DESCRIPTION "IODevice HARDWARE")

include(GNUInstallDirs)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES src/*.h)

add_library(IODevice SHARED ${SOURCE_FILES})

target_link_libraries(IODevice simple-websocket-server)
target_link_libraries(IODevice libDSP)
target_link_libraries(IODevice HAL)

set_target_properties(IODevice PROPERTIES
        PUBLIC_HEADER IODevice/src/IODevice.h)

set(COMPILER_FLAGS "-std=c++17")

target_include_directories(IODevice PUBLIC .)

install(TARGETS IODevice
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})