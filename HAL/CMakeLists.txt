cmake_minimum_required(VERSION 3.9)

project(HAL VERSION 1.0.1 DESCRIPTION "HAL -> Hardware Abstraction Layer")

include(GNUInstallDirs)

file(GLOB_RECURSE SOURCE_FILES HAL/*.cpp)
file(GLOB_RECURSE HEADER_FILES HAL/*.h)

add_library(HAL SHARED ${SOURCE_FILES})

target_link_libraries(HAL Simple-WebSocket-Server)
target_link_libraries(HAL libDSP)

set_target_properties(HAL PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER HAL/include/HAL.h)

set(COMPILER_FLAGS "-std=c++17")

target_include_directories(HAL PUBLIC .)

install(TARGETS HAL
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})