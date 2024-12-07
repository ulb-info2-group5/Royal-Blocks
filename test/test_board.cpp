#include "test_board.hpp"

#include "../src/coordinate/coordinate.hpp"
#include "../src/tetromino/tetromino_shapes.hpp"

#include <cppunit/TestAssert.h>

void BoardTest::constructorTest() {
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(20), board.getHeight());
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), board.getWidth());

    for (size_t rowIdx = 0; rowIdx < board.getHeight() - 1; rowIdx++) {
        for (size_t colIdx = 0; colIdx < board.getWidth() - 1; colIdx++) {
            CPPUNIT_ASSERT(board.get(rowIdx, colIdx).isEmpty());
        }
    }
}

void BoardTest::placeTetrominoTest() {
    tetromino = Tetromino::makeTetromino(
        TetrominoShape::L,
        Coordinate{static_cast<int>(board.getHeight() - 1), 1});

    board.placeTetromino(std::move(tetromino));

    for (size_t rowIdx = 0; rowIdx < board.getHeight(); rowIdx++) {
        for (size_t colIdx = 0; colIdx < board.getWidth(); colIdx++) {
            if ((rowIdx == board.getHeight() - 1 // bottom line of the L-shape
                 and colIdx <= 2)
                or (rowIdx == board.getHeight() - 2 // top cell of the L-shape
                    and colIdx == 2)) {
                CPPUNIT_ASSERT(!board.get(rowIdx, colIdx).isEmpty());
            } else {
                CPPUNIT_ASSERT(board.get(rowIdx, colIdx).isEmpty());
            }
        }
    }
}
