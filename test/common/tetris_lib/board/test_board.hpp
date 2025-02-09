#include "../../../../src/common/tetris_lib/board/board.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <memory>

using BoardPtr = std::unique_ptr<Board>;

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
    CPPUNIT_TEST(checkInGridTest);
    CPPUNIT_TEST(receivePenaltyLinesTest);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp() override;

    void tearDown() override;

  private:
    // #### Helpers ####
    void fillRow(int fullRowIdx);
    void fillCol(int fullColIdx);

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
    void receivePenaltyLinesTest();

  private:
    BoardPtr pBoard;
};

CPPUNIT_TEST_SUITE_REGISTRATION(BoardTest);
