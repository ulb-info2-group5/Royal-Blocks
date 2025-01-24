#include "../src/tetris/tetris.hpp"

#include "../src/tetromino/tetromino_shapes.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TetrisTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TetrisTest);
    CPPUNIT_TEST(fetchNewTetrominoTest);
    CPPUNIT_TEST(checkCanDropTest);
    CPPUNIT_TEST_SUITE_END();

  protected:
    void fetchNewTetrominoTest();
    void checkCanDropTest();

  private:
    constexpr static size_t tetrominoShapesNum =
        static_cast<size_t>(TetrominoShape::NumTetrominoShape);

    Tetris tetris;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TetrisTest);
