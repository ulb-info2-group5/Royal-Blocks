#include "../src/tetris/tetris.hpp"

#include "../src/tetromino/tetromino_shapes.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TetrisTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TetrisTest);
    CPPUNIT_TEST(constructorTest);
    CPPUNIT_TEST_SUITE_END();

  protected:
    // TODO: Find a better name for this
    void constructorTest();

  private:
    constexpr static size_t tetrominoShapesNum =
        static_cast<size_t>(TetrominoShape::NumTetrominoShape);

    Tetris tetris;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TetrisTest);
