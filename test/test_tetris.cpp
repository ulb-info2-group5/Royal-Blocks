#include "./test_tetris.hpp"

#include <cppunit/TestAssert.h>

void TetrisTest::fetchNewTetrominoTest() {
    tetris.fetchNewTetromino();
    CPPUNIT_ASSERT_EQUAL(tetrominoShapesNum - 1,
                         tetris.getTetrominoesQueueSize());
}
