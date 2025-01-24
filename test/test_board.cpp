#include "test_board.hpp"

#include "../src/tetromino/tetromino_shapes.hpp"
#include "../src/vec2/vec2.hpp"

#include <algorithm>
#include <cppunit/TestAssert.h>
#include <memory>
#include <vector>

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
    fillRow(fullRowIdx);
    CPPUNIT_ASSERT(board.checkFullRow(fullRowIdx));
    board.emptyRow(fullRowIdx);
    CPPUNIT_ASSERT(!board.checkFullRow(fullRowIdx));
}

void BoardTest::emptyColTest() {
    const unsigned fullColIdx = 0;
    fillCol(fullColIdx);
    CPPUNIT_ASSERT(board.checkFullCol(fullColIdx));
    board.emptyCol(fullColIdx);
    CPPUNIT_ASSERT(!board.checkFullCol(fullColIdx));
}

void BoardTest::gravityTest() {
    constexpr unsigned colorId = 0;

    std::vector<Vec2> cellsToBeFilled = {{0, 0}, {0, 1}, {1, 2}, {2, 1}};
    std::vector<Vec2> expectedCellsAfterGravity = {
        {0, 0}, {0, 1}, {1, 0}, {2, 0}};

    // The cells we fill before applying gravity
    for (const Vec2 &toFill : cellsToBeFilled) {
        board.at(toFill.getX(), toFill.getY()).setColorId(colorId);
    }

    board.gravity();

    for (const Vec2 &coord : expectedCellsAfterGravity) {
        if (std::find(expectedCellsAfterGravity.begin(),
                      expectedCellsAfterGravity.end(), coord)
            != expectedCellsAfterGravity.end()) {
            CPPUNIT_ASSERT(!board.get(coord.getX(), coord.getY()).isEmpty());
        } else {
            CPPUNIT_ASSERT(board.get(coord.getX(), coord.getY()).isEmpty());
        }
    }
}

void BoardTest::dropRowsAboveTest() {
    const size_t yRow0 = 0;
    const size_t yRow1 = 1;

    fillRow(yRow1);

    board.dropRowsAbove(yRow0);

    CPPUNIT_ASSERT(board.checkFullRow(yRow0));
    CPPUNIT_ASSERT(!board.checkFullRow(yRow1));
}

void BoardTest::checkInGridTest() {
    TetrominoPtr tetrominoL =
        Tetromino::makeTetromino(TetrominoShape::L, Vec2{2, 0});

    TetrominoPtr tetrominoO =
        Tetromino::makeTetromino(TetrominoShape::O, Vec2{0, 0});

    fillCol(0);

    CPPUNIT_ASSERT(board.checkInGrid(*tetrominoL));
    CPPUNIT_ASSERT(!(board.checkInGrid(*tetrominoO)));
}
