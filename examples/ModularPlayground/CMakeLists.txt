cmake_minimum_required(VERSION 3.7)
project(ModularPlaygroundExample)
set(COMPILER_FLAGS "-std=c++17 -pthread")
add_definitions(${COMPILER_FLAGS})


set(libraries
        libDSP
        libAudio
        libFilesystem
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

list(FILTER SOURCE_FILES EXCLUDE REGEX "/WebUI/")

add_executable(ModularPlaygroundExample ${SOURCE_FILES})

add_subdirectory(src/WebUI)

target_link_libraries(ModularPlaygroundExample PUBLIC webui-lib)

include_directories(ModularPlaygroundExample src)
include_directories(ModularPlaygroundExample src/WebUI)

foreach(lib ${libraries})
    target_link_libraries(ModularPlaygroundExample PRIVATE ${lib})
endforeach()

