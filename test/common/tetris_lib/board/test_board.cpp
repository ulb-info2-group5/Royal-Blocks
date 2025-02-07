#include "test_board.hpp"

#include "../src/tetromino/tetromino_shapes.hpp"
#include "../src/vec2/vec2.hpp"

#include <algorithm>
#include <cppunit/TestAssert.h>
#include <memory>
#include <vector>

void BoardTest::constructorTest() {
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(20), board.getHeight());
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), board.getWidth());

    for (int xCol = 0; xCol < static_cast<int>(board.getWidth()); xCol++) {
        for (int yRow = 0; yRow < static_cast<int>(board.getHeight()); yRow++) {
            CPPUNIT_ASSERT(board.get(xCol, yRow).isEmpty());
        }
    }
}

void BoardTest::placeTetrominoTest() {
    TetrominoPtr tetromino =
        ATetromino::makeTetromino(TetrominoShape::L, Vec2{1, 0});

    board.placeTetromino(std::move(tetromino));

    std::vector<Vec2> expectedFilledCellsCoords = {
        {0, 0}, {1, 0}, {2, 0}, {2, 1}};

    for (int yRow = 0; yRow < static_cast<int>(board.getHeight()); yRow++) {
        for (int xCol = 0; xCol < static_cast<int>(board.getWidth()); xCol++) {
            if (std::find(expectedFilledCellsCoords.begin(),
                          expectedFilledCellsCoords.end(), Vec2{xCol, yRow})
                != expectedFilledCellsCoords.end()) {
                CPPUNIT_ASSERT(!board.get(xCol, yRow).isEmpty());
            } else {
                CPPUNIT_ASSERT(board.get(xCol, yRow).isEmpty());
            }
        }
    }
}

void BoardTest::fillRow(int yRowToFill) {
    constexpr unsigned colorId = 0;

    for (int xCol = 0; xCol < static_cast<int>(board.getWidth()); xCol++) {
        board.at(xCol, yRowToFill).setColorId(colorId);
    }
}

void BoardTest::fillCol(int xColToFill) {
    constexpr unsigned colorId = 0;

    for (int yRow = 0; yRow < static_cast<int>(board.getHeight()); yRow++) {
        board.at(xColToFill, yRow).setColorId(colorId);
    }
}

void BoardTest::checkFullRowTest() {
    int bottomRowY = 0;
    fillRow(bottomRowY);

    for (int yRow = 0; yRow < static_cast<int>(board.getHeight()); yRow++) {
        bool rowIsFull = board.checkFullRow(yRow);
        CPPUNIT_ASSERT((bottomRowY == yRow) ? rowIsFull : !rowIsFull);
    }
}

void BoardTest::checkFullColTest() {
    int xFullCol = 0;
    fillCol(xFullCol);

    for (int xCol = 0; xCol < static_cast<int>(board.getWidth()); xCol++) {
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
    const int yRow0 = 0;
    const int yRow1 = 1;

    fillRow(yRow1);

    board.dropRowsAbove(yRow0);

    CPPUNIT_ASSERT(board.checkFullRow(yRow0));
    CPPUNIT_ASSERT(!board.checkFullRow(yRow1));
}

void BoardTest::checkInGridTest() {
    TetrominoPtr tetrominoL =
        ATetromino::makeTetromino(TetrominoShape::L, Vec2{2, 0});

    TetrominoPtr tetrominoO =
        ATetromino::makeTetromino(TetrominoShape::O, Vec2{0, 0});

    fillCol(0);

    CPPUNIT_ASSERT(board.checkInGrid(*tetrominoL));
    CPPUNIT_ASSERT(!(board.checkInGrid(*tetrominoO)));
}
