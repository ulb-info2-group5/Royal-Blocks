file(GLOB_RECURSE TEST_SOURCES
    *.cpp
)

if(TEST_SOURCES)
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

    target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_lib cppunit ncurses)
endif()
