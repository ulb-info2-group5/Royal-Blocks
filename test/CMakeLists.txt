file(GLOB_RECURSE TEST_SOURCES
    *.cpp
)

# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

if(TEST_SOURCES)
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

    target_link_libraries(${PROJECT_NAME}_tests PRIVATE
        tetris_royal_lib
        database_lib
        cppunit
    )
endif()
