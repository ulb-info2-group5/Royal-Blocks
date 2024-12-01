cmake_minimum_required(VERSION 3.13)

project(tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

file(GLOB_RECURSE TEST_SOURCES
    test/*.cpp
)

enable_testing()

if(TEST_SOURCES)
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

    target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} cppunit)

    include(CTest)
    add_test(coordinate ${PROJECT_NAME}_tests)
    add_test(tetromino ${PROJECT_NAME}_tests)
endif()
