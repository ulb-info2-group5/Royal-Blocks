file(GLOB_RECURSE TEST_SOURCES
    *.cpp
)

if(TEST_SOURCES)
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

    target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_lib cppunit)

    add_test(coordinate ${PROJECT_NAME}_tests)
    add_test(tetromino ${PROJECT_NAME}_tests)
    add_test(tetromino ${PROJECT_NAME}_tests)
    add_test(board ${PROJECT_NAME}_tests)
    add_test(tetris ${PROJECT_NAME}_tests)
endif()
