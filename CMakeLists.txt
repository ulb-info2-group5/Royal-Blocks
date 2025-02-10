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

# Find SQLite3 package needed for the project
find_package(SQLite3 REQUIRED)

# Enable tests for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
    add_subdirectory(test)
endif()

# tetris_lib
add_subdirectory(src/common/tetris_lib)

# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

file(GLOB_RECURSE SOURCES_TETRIS_ROYAL_LIB
    # WARN: do not include the main's here
    src/*.cpp
)

# tetris_royal_lib
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES_TETRIS_ROYAL_LIB})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link SQLite3 to the project
target_link_libraries(${PROJECT_NAME}_lib PRIVATE SQLite::SQLite3)


# glaze lib
target_include_directories(tetris_royal_lib PRIVATE ${CMAKE_SOURCE_DIR}/lib/glaze/include)
