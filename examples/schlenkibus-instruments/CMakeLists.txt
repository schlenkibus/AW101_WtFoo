cmake_minimum_required(VERSION 3.7)
project(SchlenkibusInstruments)


file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(SchlenkibusInstruments SHARED ${SOURCE_FILES})

add_definitions("-std=c++17 -fPIC")

target_link_libraries(SchlenkibusInstruments sfml-system sfml-audio webui-lib libFilesystem libDSP)