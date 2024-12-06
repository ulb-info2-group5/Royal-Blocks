#include "./test_tetris.hpp"

#include <cppunit/TestAssert.h>

void TetrisTest::constructorTest() {
    CPPUNIT_ASSERT_EQUAL(tetrominoShapesNum - 1,
                         tetris.getTetrominoesQueueSize());
}
