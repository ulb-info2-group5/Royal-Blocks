#include "test_board.hpp"

#include "../src/tetromino/tetromino_shapes.hpp"
#include "../src/vec2/vec2.hpp"

#include <algorithm>
#include <cppunit/TestAssert.h>
#include <memory>
#include <vector>

// FIXME
#include <iostream>
using namespace std;

// TODO: use int everywhere instead of size_t ?

void BoardTest::constructorTest() {
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(20), board.getHeight());
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), board.getWidth());

    for (size_t xCol = 0; xCol < board.getWidth(); xCol++) {
        for (size_t yRow = 0; yRow < board.getHeight(); yRow++) {
            CPPUNIT_ASSERT(board.get(xCol, yRow).isEmpty());
        }
    }
}

void BoardTest::placeTetrominoTest() {
    TetrominoPtr tetromino =
        Tetromino::makeTetromino(TetrominoShape::L, Vec2{1, 0});

    board.placeTetromino(std::move(tetromino));

    std::vector<Vec2> expectedFilledCellsCoords = {
        {0, 0}, {1, 0}, {2, 0}, {2, 1}};

    for (int yCoord = 0; yCoord < board.getHeight(); yCoord++) {
        for (int xCoord = 0; xCoord < board.getWidth(); xCoord++) {
            if (std::find(expectedFilledCellsCoords.begin(),
                          expectedFilledCellsCoords.end(), Vec2{xCoord, yCoord})
                != expectedFilledCellsCoords.end()) {
                CPPUNIT_ASSERT(!board.get(xCoord, yCoord).isEmpty());
            } else {
                CPPUNIT_ASSERT(board.get(xCoord, yCoord).isEmpty());
            }
        }
    }
}

void BoardTest::fillRow(size_t yRowToFill) {
    constexpr unsigned colorId = 0;

    for (int xCoord = 0; xCoord < board.getWidth(); xCoord++) {
        board.at(xCoord, yRowToFill).setColorId(colorId);
    }
}

void BoardTest::fillCol(size_t xColToFill) {
    constexpr unsigned colorId = 0;

    for (size_t yRow = 0; yRow < board.getHeight(); yRow++) {
        board.at(xColToFill, yRow).setColorId(colorId);
    }
}

void BoardTest::checkFullRowTest() {
    int bottomRowY = 0;
    fillRow(bottomRowY); // fill the bottom row

    for (size_t yRow = 0; yRow < board.getHeight(); yRow++) {
        bool rowIsFull = board.checkFullRow(yRow);
        CPPUNIT_ASSERT((bottomRowY == yRow) ? rowIsFull : !rowIsFull);
    }
}

void BoardTest::checkFullColTest() {
    int xFullCol = 0;
    fillCol(xFullCol); // fill the first column

    for (size_t xCol = 0; xCol < board.getWidth(); xCol++) {
        bool colIsFull = board.checkFullCol(xCol);
        CPPUNIT_ASSERT((xFullCol == xCol) ? colIsFull : !colIsFull);
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

void BoardTest::checkInGridTest() {
    TetrominoPtr tetrominoL = Tetromino::makeTetromino(
        TetrominoShape::L, Vec2{static_cast<int>(board.getHeight() - 1), -1});

    TetrominoPtr tetrominoO = Tetromino::makeTetromino(
        TetrominoShape::O, Vec2{static_cast<int>(board.getHeight() - 1),
                                static_cast<int>(board.getWidth() - 2)});

    fillCol(board.getWidth() - 1);

    CPPUNIT_ASSERT(!(board.checkInGrid(*tetrominoO)));
    CPPUNIT_ASSERT(board.checkInGrid(*tetrominoL));
}
