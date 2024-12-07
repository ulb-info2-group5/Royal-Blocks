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
                (std::vector<Coordinate>{{0, 0}, {-1, 0}, {-1, -1}, {0, 1}}),
                tetromino->getBody());
            break;

        case (TetrominoShape::L):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {0, -1}, {0, 1}, {-1, 1}}),
                tetromino->getBody());
            break;

        case (TetrominoShape::O):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {0, 1}, {-1, 0}, {-1, 1}}),
                tetromino->getBody());
            break;

        case (TetrominoShape::S):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {0, -1}, {-1, 0}, {-1, 1}}),
                tetromino->getBody());
            break;

        case (TetrominoShape::I):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, -1}, {0, 0}, {0, 1}, {0, 2}}),
                tetromino->getBody());
            break;

        case (TetrominoShape::J):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {0, -1}, {-1, -1}, {0, 1}}),
                tetromino->getBody());
            break;

        case (TetrominoShape::T):
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {0, 1}, {1, 0}, {0, -1}}),
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

void TetrominoTest::rotateTest() {
    for (auto &tetromino : tetrominos) {
        switch (tetromino->getShape()) {
        case (TetrominoShape::Z): // clockwise Z rotations
            tetromino->rotate(true);
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {0, 1}, {-1, 1}, {1, 0}}),
                tetromino->getBody());

            tetromino->rotate(true);
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {1, 0}, {1, 1}, {0, -1}}),
                tetromino->getBody());

            tetromino->rotate(true);
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {0, -1}, {1, -1}, {-1, 0}}),
                tetromino->getBody());

            tetromino->rotate(true);
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {-1, 0}, {-1, -1}, {0, 1}}),
                tetromino->getBody());

            break;

        case (TetrominoShape::T): // counter-clockwise T rotations
            tetromino->rotate(false);
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {-1, 0}, {0, 1}, {1, 0}}),
                tetromino->getBody());

            tetromino->rotate(false);
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {0, -1}, {-1, 0}, {0, 1}}),
                tetromino->getBody());

            tetromino->rotate(false);
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {1, 0}, {0, -1}, {-1, 0}}),
                tetromino->getBody());

            tetromino->rotate(false);
            CPPUNIT_ASSERT_EQUAL(
                (std::vector<Coordinate>{{0, 0}, {0, 1}, {1, 0}, {0, -1}}),
                tetromino->getBody());

            break;

        default:
            break;
        }
    }
}

void TetrominoTest::kicksTetrominoOTest() {
    std::unique_ptr<Tetromino> expectedTetromino;
    for (auto &tetromino : tetrominos) {
        if (!(TetrominoShape::O == tetromino->getShape())) {
            continue;
        }

        // ### testing RotationIndex = 1
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::O, {1, 2});
        rotateTetrominoNTimes(expectedTetromino, true, 1);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 2
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::O, {1, 3});
        rotateTetrominoNTimes(expectedTetromino, true, 2);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 3
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::O, {2, 3});
        rotateTetrominoNTimes(expectedTetromino, true, 3);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 4
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::O, {2, 2});
        rotateTetrominoNTimes(expectedTetromino, true, 4);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        break;
    }
}

void TetrominoTest::kicksTetrominoITest() {
    std::unique_ptr<Tetromino> expectedTetromino;
    for (auto &tetromino : tetrominos) {
        if (!(TetrominoShape::I == tetromino->getShape())) {
            continue;
        }

        // ### testing RotationIndex = 1
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {4, 5});
        rotateTetrominoNTimes(expectedTetromino, true, 1);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 2
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {5, 5});
        rotateTetrominoNTimes(expectedTetromino, true, 2);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 3
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {5, 4});
        rotateTetrominoNTimes(expectedTetromino, true, 3);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 4
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {4, 4});
        rotateTetrominoNTimes(expectedTetromino, true, 4);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);
    }
}

void TetrominoTest::kicksTetrominoLTest() {

    std::unique_ptr<Tetromino> expectedTetromino;
    for (auto &tetromino : tetrominos) {
        if (!(TetrominoShape::L == tetromino->getShape())) {
            continue;
        }

        // ### testing RotationIndex = 1
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
        rotateTetrominoNTimes(expectedTetromino, false, 1);
        // setup Tested Tetromino
        tetromino->rotate(false);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 2
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
        rotateTetrominoNTimes(expectedTetromino, false, 2);
        // setup Tested Tetromino
        tetromino->rotate(false);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 3
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
        rotateTetrominoNTimes(expectedTetromino, false, 3);
        // setup Tested Tetromino
        tetromino->rotate(false);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 4
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
        rotateTetrominoNTimes(expectedTetromino, false, 4);
        // setup Tested Tetromino
        tetromino->rotate(false);
        tetromino = tetromino->getNthKick(0);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);
    }
}
