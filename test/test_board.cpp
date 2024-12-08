#include "test_board.hpp"

#include "../src/coordinate/coordinate.hpp"
#include "../src/tetromino/tetromino_shapes.hpp"

#include <cppunit/TestAssert.h>
#include <memory>

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
    std::unique_ptr<Tetromino> tetromino = Tetromino::makeTetromino(
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

void BoardTest::fillRow(size_t fullRowIdx) {
    constexpr unsigned colorId = 0;

    for (size_t colIdx = 0; colIdx < board.getWidth(); colIdx++) {
        board.at(fullRowIdx, colIdx).setColorId(colorId);
    }
}

void BoardTest::fillCol(size_t fullColIdx) {
    constexpr unsigned colorId = 0;

    // make the 0-th column non-empty
    for (size_t rowIdx = 0; rowIdx < board.getHeight(); rowIdx++) {
        board.at(rowIdx, fullColIdx).setColorId(colorId);
    }
}

void BoardTest::checkFullRowTest() {
    size_t fullRowIdx = board.getHeight() - 1;
    fillRow(fullRowIdx);

    for (size_t rowIdx = 0; rowIdx < board.getHeight(); rowIdx++) {
        bool rowIsFull = board.checkFullRow(rowIdx);
        CPPUNIT_ASSERT((fullRowIdx == rowIdx) ? rowIsFull : !rowIsFull);
    }
}

void BoardTest::checkFullColTest() {
    const unsigned fullColIdx = 0;
    fillCol(fullColIdx);

    for (size_t colIdx = 0; colIdx < board.getWidth(); colIdx++) {
        bool colIsFull = board.checkFullCol(colIdx);
        CPPUNIT_ASSERT((fullColIdx == colIdx) ? colIsFull : !colIsFull);
    }
}

void BoardTest::emptyRowTest() {
    const unsigned fullRowIdx = 0;
    fillCol(fullRowIdx);
    board.emptyRow(fullRowIdx);
    CPPUNIT_ASSERT(!board.checkFullRow(fullRowIdx));
}

void BoardTest::emptyColTest() {
    const unsigned fullColIdx = 0;
    fillCol(fullColIdx);
    board.emptyCol(fullColIdx);
    CPPUNIT_ASSERT(!board.checkFullCol(fullColIdx));
}

void BoardTest::gravityTest() {
    constexpr unsigned colorId = 0;

    board.at(0, 0).setColorId(colorId);
    board.at(2, 0).setColorId(colorId);
    board.at(3, 0).setColorId(colorId);
    board.at(1, 1).setColorId(colorId);

    board.gravity();

    for (size_t rowIdx = 0; rowIdx < board.getHeight(); rowIdx++) {
        for (size_t colIdx = 0; colIdx < board.getWidth(); colIdx++) {
            if ((colIdx == 0 and rowIdx >= board.getHeight() - 3)
                or (colIdx == 1 and rowIdx == board.getHeight() - 1)) {
                CPPUNIT_ASSERT(!board.get(rowIdx, colIdx).isEmpty());
            } else {
                CPPUNIT_ASSERT(board.get(rowIdx, colIdx).isEmpty());
            }
        }
    }
}

void BoardTest::dropRowsAboveTest() {
    const size_t lastRowIdx = board.getHeight() - 1;
    const size_t secondLastRowIdx = board.getHeight() - 2;

    fillRow(secondLastRowIdx);

    board.dropRowsAbove(lastRowIdx);

    CPPUNIT_ASSERT(board.checkFullRow(lastRowIdx));
    CPPUNIT_ASSERT(!board.checkFullRow(secondLastRowIdx));
}
