cmake_minimum_required(VERSION 3.10)

option(BUILD_TESTS "Build test programs" OFF)

project(bcrypt)

set(CMAKE_CXX_STANDARD 11)

add_library(bcrypt src/bcrypt.cpp src/blowfish.cpp)

if(BUILD_STATIC)
    target_compile_options(bcrypt PRIVATE -static-libstdc++ -static-libgcc)
    target_link_options(bcrypt PRIVATE -static-libstdc++ -static-libgcc)
endif()

target_include_directories(bcrypt PRIVATE src/)
target_include_directories(bcrypt PUBLIC include/)

if(BUILD_TESTS)
  add_executable(test test/main.cpp)
  target_link_libraries(test PRIVATE bcrypt)
endif()
