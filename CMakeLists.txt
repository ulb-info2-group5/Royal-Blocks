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

# Enable tests for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
    add_subdirectory(test)
endif()

# tetris_royal_lib
add_subdirectory(src/common)



file(GLOB_RECURSE SOURCES_CLIENT
    ./src/client/core/*.cpp
)
set(SOURCES_MAIN main.cpp)
add_executable(main ${SOURCES_MAIN} ${SOURCES_CLIENT})
target_link_libraries(main tetris_royal_lib)


# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
