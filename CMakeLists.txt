cmake_minimum_required(VERSION 3.2)

project(AW101_FrameWork)

EXEC_PROGRAM("git"
        ${CMAKE_CURRENT_SOURCE_DIR}
        ARGS "log -1 --pretty=format:\"%ad\" --date=format:\"%Y-%m-%d %H:%M\""
        OUTPUT_VARIABLE REPO_VERSION)
message("building AW101 Framework version: ${REPO_VERSION}")

add_subdirectory(libDSP)
add_subdirectory(libAudio)
add_subdirectory(examples/ModularPlayground)
add_subdirectory(examples/FancyModule)
