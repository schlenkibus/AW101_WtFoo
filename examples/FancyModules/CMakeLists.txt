cmake_minimum_required(VERSION 3.7)
project(FancyModuleExample)


file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(FancyModuleExample SHARED ${SOURCE_FILES})

add_definitions("-std=c++17 -fPIC")

target_link_libraries(FancyModuleExample webui-lib libDSP)