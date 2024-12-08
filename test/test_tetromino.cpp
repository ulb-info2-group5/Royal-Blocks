#include "test_tetromino.hpp"

#include "../src/tetromino/tetromino.hpp"
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
         static_cast<TetrominoShape>(i) < TetrominoShape::NumTetrominoShape;
         i++) {
        tetrominoes.emplace_back(Tetromino::makeTetromino(
            static_cast<TetrominoShape>(i),
            Coordinate(i, i))); // Coordinate(i, i) to check that the
                                // translation in constructor is working
    }
}

void TetrominoTest::tearDown() {
    for (auto &tetromino : tetrominoes) {
        tetromino.reset();
    }
}

void TetrominoTest::shapeTest() {
    for (const auto &tetromino : tetrominoes) {
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
    for (const auto &tetromino : tetrominoes) {
        switch (tetromino->getShape()) {
        case (TetrominoShape::Z):
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2),
                                 tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), tetromino->getWidth());
            break;

        case (TetrominoShape::L):
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2),
                                 tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), tetromino->getWidth());
            break;

        case (TetrominoShape::O):
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2),
                                 tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), tetromino->getWidth());
            break;

        case (TetrominoShape::S):
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2),
                                 tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), tetromino->getWidth());
            break;

        case (TetrominoShape::I):
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1),
                                 tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), tetromino->getWidth());
            break;

        case (TetrominoShape::J):
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2),
                                 tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), tetromino->getWidth());
            break;

        case (TetrominoShape::T):
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2),
                                 tetromino->getHeight());
            CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), tetromino->getWidth());
            break;
        default:
            break;
        }
    }
}

void TetrominoTest::moveTest() {
    CPPUNIT_ASSERT_EQUAL(Coordinate(0, 0), tetrominoes[0]->getAnchorPoint());

    tetrominoes[0]->move(Direction::Down);

    CPPUNIT_ASSERT_EQUAL(Coordinate(1, 0), tetrominoes[0]->getAnchorPoint());

    tetrominoes[0]->move(Direction::Right);

    CPPUNIT_ASSERT_EQUAL(Coordinate(1, 1), tetrominoes[0]->getAnchorPoint());

    tetrominoes[0]->move(Direction::Left);

    CPPUNIT_ASSERT_EQUAL(Coordinate(1, 0), tetrominoes[0]->getAnchorPoint());
}

void TetrominoTest::rotateTest() {
    for (auto &tetromino : tetrominoes) {
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

void TetrominoTest::offset1TetrominoOTest() {
    std::unique_ptr<Tetromino> expectedTetromino;
    for (auto &tetromino : tetrominoes) {
        if (!(TetrominoShape::O == tetromino->getShape())) {
            continue;
        }

        // ### testing RotationIndex = 1
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::O, {1, 2});
        rotateTetrominoNTimes(expectedTetromino, true, 1);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 2
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::O, {1, 3});
        rotateTetrominoNTimes(expectedTetromino, true, 2);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 3
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::O, {2, 3});
        rotateTetrominoNTimes(expectedTetromino, true, 3);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 4
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::O, {2, 2});
        rotateTetrominoNTimes(expectedTetromino, true, 4);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        break;
    }
}

void TetrominoTest::offset1TetrominoITest() {
    std::unique_ptr<Tetromino> expectedTetromino;
    for (auto &tetromino : tetrominoes) {
        if (!(TetrominoShape::I == tetromino->getShape())) {
            continue;
        }

        // ### testing RotationIndex = 1
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {4, 5});
        rotateTetrominoNTimes(expectedTetromino, true, 1);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 2
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {5, 5});
        rotateTetrominoNTimes(expectedTetromino, true, 2);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 3
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {5, 4});
        rotateTetrominoNTimes(expectedTetromino, true, 3);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 4
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {4, 4});
        rotateTetrominoNTimes(expectedTetromino, true, 4);

        // setup Tested Tetromino
        tetromino->rotate(true);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);
    }
}

void TetrominoTest::offset1TetrominoLTest() {

    std::unique_ptr<Tetromino> expectedTetromino;
    for (auto &tetromino : tetrominoes) {
        if (!(TetrominoShape::L == tetromino->getShape())) {
            continue;
        }

        // ### testing RotationIndex = 1
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
        rotateTetrominoNTimes(expectedTetromino, false, 1);
        // setup Tested Tetromino
        tetromino->rotate(false);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 2
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
        rotateTetrominoNTimes(expectedTetromino, false, 2);
        // setup Tested Tetromino
        tetromino->rotate(false);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 3
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
        rotateTetrominoNTimes(expectedTetromino, false, 3);
        // setup Tested Tetromino
        tetromino->rotate(false);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);

        // ### testing RotationIndex = 4
        // setup Expected
        expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
        rotateTetrominoNTimes(expectedTetromino, false, 4);
        // setup Tested Tetromino
        tetromino->rotate(false);
        tetromino = tetromino->getNthOffset(1);

        CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetromino);
    }
}

void TetrominoTest::variousOffsetsTetrominoLTest() {
    // ### testing offsetIndex = 2 and clockwise rotation
    std::unique_ptr<Tetromino> tetrominoL =
        Tetromino::makeTetromino(TetrominoShape::L, {1, 1}); // setup Expected
    std::unique_ptr<Tetromino> expectedTetromino =
        Tetromino::makeTetromino(TetrominoShape::L, {1, 0});
    rotateTetrominoNTimes(expectedTetromino, true, 1);
    tetrominoL->rotate(true);
    tetrominoL = tetrominoL->getNthOffset(2);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetrominoL);

    // ### testing offsetIndex = 3 and counter-clockwise rotation
    tetrominoL = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
    expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {0, 2});
    rotateTetrominoNTimes(expectedTetromino, false, 1);
    tetrominoL->rotate(false);
    tetrominoL = tetrominoL->getNthOffset(3);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetrominoL);

    // ### testing offsetIndex = 5 and clockwise rotation
    tetrominoL = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
    expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {3, 0});
    rotateTetrominoNTimes(expectedTetromino, true, 1);
    tetrominoL->rotate(true);
    tetrominoL = tetrominoL->getNthOffset(5);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetrominoL);

    // ### testing offsetIndex = 4 then offsetIndex = 3 and clockwise rotation
    tetrominoL = Tetromino::makeTetromino(TetrominoShape::L, {1, 1});
    expectedTetromino = Tetromino::makeTetromino(TetrominoShape::L, {4, 2});
    rotateTetrominoNTimes(expectedTetromino, true, 2);
    tetrominoL->rotate(true);
    tetrominoL = tetrominoL->getNthOffset(4);
    tetrominoL->rotate(true);
    tetrominoL = tetrominoL->getNthOffset(3);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetrominoL);
}

void TetrominoTest::variousOffsetsTetrominoITest() {
    // ### testing offsetIndex = 1 and clockwise rotation
    std::unique_ptr<Tetromino> tetrominoI =
        Tetromino::makeTetromino(TetrominoShape::I, {1, 1});
    std::unique_ptr<Tetromino> expectedTetromino =
        Tetromino::makeTetromino(TetrominoShape::I, {1, 2});
    rotateTetrominoNTimes(expectedTetromino, true, 1);
    tetrominoI->rotate(true);
    tetrominoI = tetrominoI->getNthOffset(1);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetrominoI);

    // ### testing offsetIndex = 2 and counter-clockwise rotation
    tetrominoI = Tetromino::makeTetromino(TetrominoShape::I, {1, 1});
    expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {2, 0});
    rotateTetrominoNTimes(expectedTetromino, false, 1);
    tetrominoI->rotate(false);
    tetrominoI = tetrominoI->getNthOffset(2);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetrominoI);

    // ### testing offsetIndex = 4 and clockwise rotation
    tetrominoI = Tetromino::makeTetromino(TetrominoShape::I, {1, 1});
    expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {2, 0});
    rotateTetrominoNTimes(expectedTetromino, true, 1);
    tetrominoI->rotate(true);
    tetrominoI = tetrominoI->getNthOffset(4);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetrominoI);

    // ### testing offsetIndex = 5 and counter-clockwise rotation
    tetrominoI = Tetromino::makeTetromino(TetrominoShape::I, {1, 1});
    expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {3, 3});
    rotateTetrominoNTimes(expectedTetromino, false, 1);
    tetrominoI->rotate(false);
    tetrominoI = tetrominoI->getNthOffset(5);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetrominoI);

    // ### testing offsetIndex = 4 then offsetIndex = 2 and counter-clockwise
    // rotation
    tetrominoI = Tetromino::makeTetromino(TetrominoShape::I, {1, 1});
    expectedTetromino = Tetromino::makeTetromino(TetrominoShape::I, {0, -1});
    rotateTetrominoNTimes(expectedTetromino, false, 2);
    tetrominoI->rotate(false);
    tetrominoI = tetrominoI->getNthOffset(4);
    tetrominoI->rotate(false);
    tetrominoI = tetrominoI->getNthOffset(2);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tetrominoI);
}
