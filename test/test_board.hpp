#include "../src/board/board.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class BoardTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(BoardTest);
    CPPUNIT_TEST(constructorTest);
    CPPUNIT_TEST(placeTetrominoTest);
    CPPUNIT_TEST(checkFullRowTest);
    CPPUNIT_TEST(checkFullColTest);
    CPPUNIT_TEST(emptyRowTest);
    CPPUNIT_TEST(emptyColTest);
    CPPUNIT_TEST(gravityTest);
    CPPUNIT_TEST(dropRowsAboveTest);
    // missing test: checkInGridTest()
    CPPUNIT_TEST_SUITE_END();

  private:
    // #### Helpers ####
    void fillRow(size_t fullRowIdx);
    void fillCol(size_t fullColIdx);

  protected:
    void constructorTest();
    void placeTetrominoTest();
    void checkFullRowTest();
    void checkFullColTest();
    void emptyRowTest();
    void emptyColTest();
    void gravityTest();
    void dropRowsAboveTest();
    void checkInGridTest();

  private:
    Board board;
};

CPPUNIT_TEST_SUITE_REGISTRATION(BoardTest);
