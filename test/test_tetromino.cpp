#include "test_tetromino.hpp"

#include "../src/tetromino/tetromino.hpp"
#include "../src/tetromino/tetromino_shapes.hpp"
#include "utils.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>
#include <vector>

// NOTE: Haven't written tests for rotate() yet since we don't want to have to
// write them again when we will switch to Super Rotation System algorithm

void TetrominoTest::setUp() {
    for (int i = 0;
         static_cast<TetrominoShape>(i) < TetrominoShape::NUM_TETROMINOSHAPE;
         i++) {
        tetrominos.emplace_back(Tetromino::makeTetromino(
            static_cast<TetrominoShape>(i),
            Coordinate(i, i))); // Coordinate(i, i) to check that the
                                // translation in constructor is working
    }
}

void TetrominoTest::tearDown() {
    for (auto &tetromino : tetrominos) {
        tetromino.reset();
    }
}

void TetrominoTest::shapeTest() {
    for (const auto &tetromino : tetrominos) {
        switch (tetromino->getShape()) {
        case (TetrominoShape::Z):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                         Coordinate{1, 1}, Coordinate{1, 2}}),
                tetromino->getBody());
            break;

        case (TetrominoShape::L):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{Coordinate(0, 2), Coordinate(1, 2),
                                         Coordinate(1, 1), Coordinate(1, 0)}),
                tetromino->getBody());
            break;

        case (TetrominoShape::O):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                         Coordinate{1, 0}, Coordinate{1, 1}}),
                tetromino->getBody());
            break;

        case (TetrominoShape::S):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{Coordinate{0, 1}, Coordinate{0, 2},
                                         Coordinate{1, 0}, Coordinate{1, 1}}),
                tetromino->getBody());
            break;

        case (TetrominoShape::I):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{Coordinate(0, 0), Coordinate(0, 1),
                                         Coordinate(0, 2), Coordinate(0, 3)}),
                tetromino->getBody());
            break;

        case (TetrominoShape::J):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{1, 0},
                                         Coordinate{1, 1}, Coordinate{1, 2}}),
                tetromino->getBody());
            break;

        case (TetrominoShape::T):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                         Coordinate{0, 2}, Coordinate{1, 1}}),
                tetromino->getBody());
            break;
        default:
            break;
        }
    }
}

void TetrominoTest::getWidthAndHeightTest() {
    for (const auto &tetromino : tetrominos) {
        switch (tetromino->getShape()) {
        case (TetrominoShape::Z):
            CPPUNIT_ASSERT_EQUAL(2, tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(3, tetromino->getWidth());
            break;

        case (TetrominoShape::L):
            CPPUNIT_ASSERT_EQUAL(2, tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(3, tetromino->getWidth());
            break;

        case (TetrominoShape::O):
            CPPUNIT_ASSERT_EQUAL(2, tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(2, tetromino->getWidth());
            break;

        case (TetrominoShape::S):
            CPPUNIT_ASSERT_EQUAL(2, tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(3, tetromino->getWidth());
            break;

        case (TetrominoShape::I):
            CPPUNIT_ASSERT_EQUAL(1, tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(4, tetromino->getWidth());
            break;

        case (TetrominoShape::J):
            CPPUNIT_ASSERT_EQUAL(2, tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(3, tetromino->getWidth());
            break;

        case (TetrominoShape::T):
            CPPUNIT_ASSERT_EQUAL(2, tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(3, tetromino->getWidth());
            break;
        default:
            break;
        }
    }
}

void TetrominoTest::moveTest() {
    CPPUNIT_ASSERT_EQUAL(Coordinate(0, 0), tetrominos[0]->getAnchorPoint());

    tetrominos[0]->move(Direction::down);

    CPPUNIT_ASSERT_EQUAL(Coordinate(1, 0), tetrominos[0]->getAnchorPoint());

    tetrominos[0]->move(Direction::right);

    CPPUNIT_ASSERT_EQUAL(Coordinate(1, 1), tetrominos[0]->getAnchorPoint());

    tetrominos[0]->move(Direction::left);

    CPPUNIT_ASSERT_EQUAL(Coordinate(1, 0), tetrominos[0]->getAnchorPoint());
}
