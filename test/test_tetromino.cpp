#include "test_tetromino.hpp"

#include "../src/tetromino/tetromino.hpp"
#include "../src/tetromino/tetromino_shapes.hpp"
#include "utils.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>
#include <vector>

void TetrominoTest::setUp() {
    for (int i = 0;
         static_cast<TetrominoShape>(i) < TetrominoShape::NUM_TETROMINOSHAPE;
         i++) {
        tetrominos.emplace_back(Tetromino::makeTetromino(
            static_cast<TetrominoShape>(i), Coordinate(i, i)));
    }
}

void TetrominoTest::tearDown() {
    for (auto &tetromino : tetrominos) {
        tetromino.reset();
    }
}

void TetrominoTest::gettersTest() {
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
