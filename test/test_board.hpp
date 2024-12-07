#include "../src/board/board.hpp"

#include "../src/tetromino/tetromino.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <memory>

// TODO: test checkInGrid

class BoardTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(BoardTest);
    CPPUNIT_TEST(constructorTest);
    CPPUNIT_TEST(placeTetrominoTest);
    CPPUNIT_TEST(checkFullRowTest);
    CPPUNIT_TEST(checkFullColTest);
    CPPUNIT_TEST(emptyRowTest);
    CPPUNIT_TEST(emptyColTest);
    CPPUNIT_TEST_SUITE_END();

  private:
    // #### Helpers ####
    void fillRow(size_t fullRowIdx);
    void fillCol(size_t fullColIdx);

  protected:
    // TODO: Find a better name for this
    void constructorTest();
    void placeTetrominoTest();
    void checkFullRowTest();
    void checkFullColTest();
    void emptyRowTest();
    void emptyColTest();

  private:
    Board board;
    std::unique_ptr<Tetromino> tetromino;
};

CPPUNIT_TEST_SUITE_REGISTRATION(BoardTest);
