#include "./test_tetris.hpp"

#include "../src/tetromino/tetromino_shapes.hpp"

#include <cppunit/TestAssert.h>

void TetrisTest::constructorTest() {
    CPPUNIT_ASSERT_EQUAL(
        static_cast<size_t>(TetrominoShape::NUM_TETROMINOSHAPE),
        tetris.getTetrominoesQueueSize());
}
