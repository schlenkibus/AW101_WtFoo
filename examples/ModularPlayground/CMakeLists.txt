cmake_minimum_required(VERSION 3.7)
project(ModularPlaygroundExample)
set(COMPILER_FLAGS "-std=c++17 -pthread")
add_definitions(${COMPILER_FLAGS})


set(libraries
        libDSP
        libAudio
        libFilesystem
        webui-lib
        pthread
        m
        wthttp
        boost_system
        HAL
        simple-websocket-server
        stdc++fs
        wt
        dl)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_executable(ModularPlaygroundExample ${SOURCE_FILES})
include_directories(ModularPlaygroundExample src)

foreach(lib ${libraries})
    target_link_libraries(ModularPlaygroundExample PRIVATE ${lib})
endforeach()

