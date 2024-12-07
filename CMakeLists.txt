cmake_minimum_required(VERSION 3.13)

project(tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=thread")

enable_testing()

add_subdirectory(test)

file(GLOB_RECURSE SOURCES_LIB
    src/board/*.cpp
    src/coordinate/*.cpp
    src/tetris/*.cpp
    src/tetromino/*.cpp
)

add_library(${PROJECT_NAME}_lib ${SOURCES_LIB})

set(SOURCES_MAIN src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES_MAIN})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
