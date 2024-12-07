#include "../src/board/board.hpp"

#include "../src/tetromino/tetromino.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class BoardTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(BoardTest);
    CPPUNIT_TEST(constructorTest);
    CPPUNIT_TEST(placeTetrominoTest);
    CPPUNIT_TEST_SUITE_END();

  protected:
    // TODO: Find a better name for this
    void constructorTest();
    void placeTetrominoTest();

  private:
    Board board;
    std::unique_ptr<Tetromino> tetromino;
};

CPPUNIT_TEST_SUITE_REGISTRATION(BoardTest);
