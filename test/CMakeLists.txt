file(GLOB_RECURSE TEST_SOURCES
    *.cpp
)

if(TEST_SOURCES)
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

    target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_lib cppunit ncurses)

    add_test(vec2 ${PROJECT_NAME}_tests)
    add_test(tetromino ${PROJECT_NAME}_tests)
    # TODO: add the other tests
endif()
