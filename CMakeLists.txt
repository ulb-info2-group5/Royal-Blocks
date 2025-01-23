cmake_minimum_required(VERSION 3.15)

# Compile & linking options
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug build.")
    add_compile_options(-std=c++20 -g -pedantic -Wall -Wextra -fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
else(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release build.")
    add_compile_options(-std=c++20 -O2 -w)
endif()

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(tetris)

# Enable tests for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
    add_subdirectory(test)
endif()

# tetris_lib source files
file(GLOB_RECURSE SOURCES_LIB
    src/board/*.cpp
    src/vec2/*.cpp
    src/tetris/*.cpp
    src/tetromino/*.cpp
    src/grid/*.cpp
)

# Ncurses
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# add tetris_lib as lib
add_library(${PROJECT_NAME}_lib ${SOURCES_LIB})

# main.cpp
set(SOURCES_MAIN src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES_MAIN})

# link main with tetris_lib and ncurses
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib ${CURSES_LIBRARIES})
