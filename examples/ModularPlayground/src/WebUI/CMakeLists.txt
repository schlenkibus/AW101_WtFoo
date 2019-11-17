cmake_minimum_required(VERSION 3.7)
project(WebUI)
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

add_library(webui-lib STATIC ${WEBUI_SOURCES} ${WEBUI_HEADER})
foreach(lib ${libraries})
    link_libraries(webui-lib lib)
endforeach()

add_executable(ModularPlaygroundExample ${SOURCE_FILES})
include_directories(ModularPlaygroundExample src)
target_link_libraries(ModularPlaygroundExample webui-lib)

foreach(lib ${libraries})
    target_link_libraries(ModularPlaygroundExample lib)
endforeach()

