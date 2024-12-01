#include "test_tetromino.hpp"

#include "../src/tetromino/tetromino.hpp"
#include "../src/tetromino/tetromino_shapes.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>

void TetrominoTest::setUp() {
    tetromino_ = Tetromino::makeTetromino(TetrominoShape::I, Coordinate(0, 0));
}

void TetrominoTest::tearDown() {}

void TetrominoTest::tetrominoCreationTest() {
    CPPUNIT_ASSERT(tetromino_ != nullptr);

    CPPUNIT_ASSERT_EQUAL(tetromino_->getAnchorPoint(), Coordinate(0, 0));
}
