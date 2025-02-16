file(GLOB_RECURSE TEST_SOURCES
    *.cpp
)

# Make lsp's aware of our libraries (make includes work basically)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

if(TEST_SOURCES)
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

    # TODO: link against more than just tetris_lib
    # (tetris_royal_lib and all libs that we wrote tests for)
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE tetris_lib cppunit)
endif()
