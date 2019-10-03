cmake_minimum_required(VERSION 3.9)

project(libFilesystem VERSION 1.0.1 DESCRIPTION "libFilesystem offers generic File and Directory algorithms and classes implementation based on the std::filesystem")

include(GNUInstallDirs)

file(GLOB_RECURSE SOURCE_FILES libFilesystem/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES libFilesystem/include/*.h)

add_library(libFilesystem SHARED ${SOURCE_FILES})

target_link_libraries(libFilesystem stdc++fs)

set_target_properties(libFilesystem PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER libFilesystem/include/libFilesystem.h)

set(COMPILER_FLAGS "-std=c++17")

configure_file(libFilesystem.pc.in libFilesystem.pc @ONLY)

target_include_directories(libFilesystem PUBLIC .)

install(TARGETS libFilesystem
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/libFilesystem.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)