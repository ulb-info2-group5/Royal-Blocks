cmake_minimum_required(VERSION 3.13)

project(tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
