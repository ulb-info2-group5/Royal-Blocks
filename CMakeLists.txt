cmake_minimum_required(VERSION 3.15)

# Compile & linking options
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug build.")
    add_compile_options(-std=c++23 -g -pedantic -Wall -Wextra -fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
else(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release build.")
    add_compile_options(-std=c++23 -O2 -w)
endif()

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(tetris_royal)

# Find FTXUI package needed for the project
find_package(ftxui REQUIRED)

# Enable tests for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
    add_subdirectory(test)
endif()


file(GLOB_RECURSE SOURCES_TETRIS_ROYAL_LIB
    # WARN: do not include the main's here
    src/*.cpp
)


# Create a library with the project's sources
add_library(${PROJECT_NAME}_lib ${SOURCES_TETRIS_ROYAL_LIB})


# Link SQLite3 and FTXUI to the project
target_link_libraries(${PROJECT_NAME}_lib PRIVATE ftxui::screen ftxui::dom ftxui::component)
