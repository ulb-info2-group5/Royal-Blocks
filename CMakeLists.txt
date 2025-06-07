cmake_minimum_required(VERSION 3.15)

option(BUILD_STATIC "Link standard libs statically (but keep Qt dynamic)" OFF)

if(BUILD_STATIC)
    message(STATUS "Static linking of libstdc++/libgcc")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    set(BUILD_SHARED_LIBS ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
endif()

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0600)
endif()

# Compile & linking options
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug build.")
    add_link_options(-fsanitize=address,undefined)
    add_compile_options(-O0 -g3 -fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
else()
    message("Release build.")
    add_compile_options(-O3 -march=native -DNDEBUG)
    add_link_options(-O3 -march=native)
endif()

project(royal-blocks)

# Enable tests for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
    # add_subdirectory(test)
endif()

add_subdirectory(lib)

add_subdirectory(src/common)
add_subdirectory(src/client)
add_subdirectory(src/server)
