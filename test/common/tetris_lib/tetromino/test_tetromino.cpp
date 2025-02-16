#include "test_tetromino.hpp"

#include "../../../utils.hpp"
#include "tetromino/tetromino_shapes.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

void TetrominoTest::setUp() {
    pTetrominoZ = ATetromino::makeTetromino(TetrominoShape::Z, Vec2(0, 0));
    pTetrominoL = ATetromino::makeTetromino(TetrominoShape::L, Vec2(0, 0));
    pTetrominoO = ATetromino::makeTetromino(TetrominoShape::O, Vec2(0, 0));
    pTetrominoS = ATetromino::makeTetromino(TetrominoShape::S, Vec2(0, 0));
    pTetrominoI = ATetromino::makeTetromino(TetrominoShape::I, Vec2(0, 0));
    pTetrominoJ = ATetromino::makeTetromino(TetrominoShape::J, Vec2(0, 0));
    pTetrominoT = ATetromino::makeTetromino(TetrominoShape::T, Vec2(0, 0));
}

void TetrominoTest::tearDown() {}

void TetrominoTest::shapeTest() {
    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {0, 1}, {-1, 1}, {1, 0}}),
                         pTetrominoZ->getBody());

    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {-1, 0}, {1, 0}, {1, 1}}),
                         pTetrominoL->getBody());

    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {0, 1}, {1, 1}, {1, 0}}),
                         pTetrominoO->getBody());

    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {-1, 0}, {0, 1}, {1, 1}}),
                         pTetrominoS->getBody());

    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {-1, 0}, {1, 0}, {2, 0}}),
                         pTetrominoI->getBody());

    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {-1, 0}, {-1, 1}, {1, 0}}),
                         pTetrominoJ->getBody());

    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {1, 0}, {0, -1}, {-1, 0}}),
                         pTetrominoT->getBody());
}

void TetrominoTest::getWidthAndHeightTest() {
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), pTetrominoZ->getHeight());
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), pTetrominoZ->getWidth());

    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), pTetrominoL->getHeight());
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), pTetrominoL->getWidth());

    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), pTetrominoO->getHeight());
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), pTetrominoO->getWidth());

    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), pTetrominoS->getHeight());
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), pTetrominoS->getWidth());

    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), pTetrominoI->getHeight());
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), pTetrominoI->getWidth());

    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), pTetrominoJ->getHeight());
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), pTetrominoJ->getWidth());

    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), pTetrominoT->getHeight());
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), pTetrominoT->getWidth());
}

void TetrominoTest::moveTest() {
    CPPUNIT_ASSERT_EQUAL(Vec2(0, 0), pTetrominoZ->getAnchorPoint());

    pTetrominoZ->move(Direction::Down);

    CPPUNIT_ASSERT_EQUAL(Vec2(0, -1), pTetrominoZ->getAnchorPoint());

    pTetrominoZ->move(Direction::Right);

    CPPUNIT_ASSERT_EQUAL(Vec2(1, -1), pTetrominoZ->getAnchorPoint());

    pTetrominoZ->move(Direction::Left);

    CPPUNIT_ASSERT_EQUAL(Vec2(0, -1), pTetrominoZ->getAnchorPoint());
}

void TetrominoTest::rotateTest() {
    pTetrominoZ->rotate(true);
    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {1, 0}, {1, 1}, {0, -1}}),
                         pTetrominoZ->getBody());

    pTetrominoZ->rotate(true);
    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {0, -1}, {1, -1}, {-1, 0}}),
                         pTetrominoZ->getBody());

    pTetrominoZ->rotate(true);
    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {-1, 0}, {-1, -1}, {0, 1}}),
                         pTetrominoZ->getBody());

    pTetrominoZ->rotate(true);
    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {0, 1}, {-1, 1}, {1, 0}}),
                         pTetrominoZ->getBody());

    pTetrominoT->rotate(false);
    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {0, 1}, {1, 0}, {0, -1}}),
                         pTetrominoT->getBody());

    pTetrominoT->rotate(false);
    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {-1, 0}, {0, 1}, {1, 0}}),
                         pTetrominoT->getBody());

    pTetrominoT->rotate(false);
    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {0, -1}, {-1, 0}, {0, 1}}),
                         pTetrominoT->getBody());

    pTetrominoT->rotate(false);
    CPPUNIT_ASSERT_EQUAL((std::vector<Vec2>{{0, 0}, {1, 0}, {0, -1}, {-1, 0}}),
                         pTetrominoT->getBody());
}

void TetrominoTest::offset1TetrominoOTest() {
    TetrominoPtr expectedTetromino;

    // ### testing RotationIndex = 1
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::O, {0, 1});
    rotateTetrominoNTimes(expectedTetromino, true, 1);

    // setup Tested Tetromino
    pTetrominoO->rotate(true);
    pTetrominoO = pTetrominoO->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoO);

    // ### testing RotationIndex = 2
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::O, {1, 1});
    rotateTetrominoNTimes(expectedTetromino, true, 2);

    // setup Tested Tetromino
    pTetrominoO->rotate(true);
    pTetrominoO = pTetrominoO->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoO);

    // ### testing RotationIndex = 3
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::O, {1, 0});
    rotateTetrominoNTimes(expectedTetromino, true, 3);

    // setup Tested Tetromino
    pTetrominoO->rotate(true);
    pTetrominoO = pTetrominoO->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoO);

    // ### testing RotationIndex = 4
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::O, {0, 0});
    rotateTetrominoNTimes(expectedTetromino, true, 4);

    // setup Tested Tetromino
    pTetrominoO->rotate(true);
    pTetrominoO = pTetrominoO->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoO);
}

void TetrominoTest::offset1TetrominoITest() {
    TetrominoPtr expectedTetromino;

    // ### testing RotationIndex = 1
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::I, {1, 0});
    rotateTetrominoNTimes(expectedTetromino, true, 1);

    // setup Tested Tetromino
    pTetrominoI->rotate(true);
    pTetrominoI = pTetrominoI->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoI);

    // ### testing RotationIndex = 2
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::I, {1, -1});
    rotateTetrominoNTimes(expectedTetromino, true, 2);

    // setup Tested Tetromino
    pTetrominoI->rotate(true);
    pTetrominoI = pTetrominoI->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoI);

    // ### testing RotationIndex = 3
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::I, {0, -1});
    rotateTetrominoNTimes(expectedTetromino, true, 3);

    // setup Tested Tetromino
    pTetrominoI->rotate(true);
    pTetrominoI = pTetrominoI->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoI);

    // ### testing RotationIndex = 4
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::I, {0, 0});
    rotateTetrominoNTimes(expectedTetromino, true, 4);

    // setup Tested Tetromino
    pTetrominoI->rotate(true);
    pTetrominoI = pTetrominoI->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoI);
}

void TetrominoTest::offset1TetrominoLTest() {
    TetrominoPtr expectedTetromino;

    // ### testing RotationIndex = 1
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::L, {0, 0});
    rotateTetrominoNTimes(expectedTetromino, false, 1);
    // setup Tested Tetromino
    pTetrominoL->rotate(false);
    pTetrominoL = pTetrominoL->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoL);

    // ### testing RotationIndex = 2
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::L, {0, 0});
    rotateTetrominoNTimes(expectedTetromino, false, 2);
    // setup Tested Tetromino
    pTetrominoL->rotate(false);
    pTetrominoL = pTetrominoL->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoL);

    // ### testing RotationIndex = 3
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::L, {0, 0});
    rotateTetrominoNTimes(expectedTetromino, false, 3);
    // setup Tested Tetromino
    pTetrominoL->rotate(false);
    pTetrominoL = pTetrominoL->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoL);

    // ### testing RotationIndex = 4
    // setup Expected
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::L, {0, 0});
    rotateTetrominoNTimes(expectedTetromino, false, 4);
    // setup Tested Tetromino
    pTetrominoL->rotate(false);
    pTetrominoL = pTetrominoL->getNthOffset(1);

    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *pTetrominoL);
}

void TetrominoTest::variousOffsetsTetrominoLTest() {
    // ### testing offsetIndex = 2 and clockwise rotation
    TetrominoPtr tmpTetrominoL =
        ATetromino::makeTetromino(TetrominoShape::L, {1, 1}); // setup Expected
    TetrominoPtr expectedTetromino =
        ATetromino::makeTetromino(TetrominoShape::L, {0, 1});
    rotateTetrominoNTimes(expectedTetromino, true, 1);
    tmpTetrominoL->rotate(true);
    tmpTetrominoL = tmpTetrominoL->getNthOffset(2);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tmpTetrominoL);

    // ### testing offsetIndex = 3 and counter-clockwise rotation
    tmpTetrominoL = ATetromino::makeTetromino(TetrominoShape::L, {1, 1});
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::L, {2, 2});
    rotateTetrominoNTimes(expectedTetromino, false, 1);
    tmpTetrominoL->rotate(false);
    tmpTetrominoL = tmpTetrominoL->getNthOffset(3);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tmpTetrominoL);

    // ### testing offsetIndex = 5 and clockwise rotation
    tmpTetrominoL = ATetromino::makeTetromino(TetrominoShape::L, {1, 1});
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::L, {0, -1});
    rotateTetrominoNTimes(expectedTetromino, true, 1);
    tmpTetrominoL->rotate(true);
    tmpTetrominoL = tmpTetrominoL->getNthOffset(5);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tmpTetrominoL);

    // ### testing offsetIndex = 4 then offsetIndex = 3 and clockwise
    // rotation
    tmpTetrominoL = ATetromino::makeTetromino(TetrominoShape::L, {1, 1});
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::L, {2, -2});
    rotateTetrominoNTimes(expectedTetromino, true, 2);
    tmpTetrominoL->rotate(true);
    tmpTetrominoL = tmpTetrominoL->getNthOffset(4);
    tmpTetrominoL->rotate(true);
    tmpTetrominoL = tmpTetrominoL->getNthOffset(3);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tmpTetrominoL);
}

void TetrominoTest::variousOffsetsTetrominoITest() {
    // ### testing offsetIndex = 1 and clockwise rotation
    TetrominoPtr tmpTetrominoI =
        ATetromino::makeTetromino(TetrominoShape::I, {1, 1});
    TetrominoPtr expectedTetromino =
        ATetromino::makeTetromino(TetrominoShape::I, {2, 1});
    rotateTetrominoNTimes(expectedTetromino, true, 1);
    tmpTetrominoI->rotate(true);
    tmpTetrominoI = tmpTetrominoI->getNthOffset(1);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tmpTetrominoI);

    // ### testing offsetIndex = 2 and counter-clockwise rotation
    tmpTetrominoI = ATetromino::makeTetromino(TetrominoShape::I, {1, 1});
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::I, {0, 0});
    rotateTetrominoNTimes(expectedTetromino, false, 1);
    tmpTetrominoI->rotate(false);
    tmpTetrominoI = tmpTetrominoI->getNthOffset(2);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tmpTetrominoI);

    // ### testing offsetIndex = 4 and clockwise rotation
    tmpTetrominoI = ATetromino::makeTetromino(TetrominoShape::I, {1, 1});
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::I, {0, 0});
    rotateTetrominoNTimes(expectedTetromino, true, 1);
    tmpTetrominoI->rotate(true);
    tmpTetrominoI = tmpTetrominoI->getNthOffset(4);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tmpTetrominoI);

    // ### testing offsetIndex = 5 and counter-clockwise rotation
    tmpTetrominoI = ATetromino::makeTetromino(TetrominoShape::I, {1, 1});
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::I, {3, -1});
    rotateTetrominoNTimes(expectedTetromino, false, 1);
    tmpTetrominoI->rotate(false);
    tmpTetrominoI = tmpTetrominoI->getNthOffset(5);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tmpTetrominoI);

    // ### testing offsetIndex = 4 then offsetIndex = 2 and
    // counter-clockwise rotation
    tmpTetrominoI = ATetromino::makeTetromino(TetrominoShape::I, {1, 1});
    expectedTetromino = ATetromino::makeTetromino(TetrominoShape::I, {-1, 2});
    rotateTetrominoNTimes(expectedTetromino, false, 2);
    tmpTetrominoI->rotate(false);
    tmpTetrominoI = tmpTetrominoI->getNthOffset(4);
    tmpTetrominoI->rotate(false);
    tmpTetrominoI = tmpTetrominoI->getNthOffset(2);
    CPPUNIT_ASSERT_EQUAL(*expectedTetromino, *tmpTetrominoI);
}
