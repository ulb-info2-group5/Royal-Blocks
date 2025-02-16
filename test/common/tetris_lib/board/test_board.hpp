#include "board/board.hpp"

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
    CPPUNIT_TEST(receivePenaltyOutOfBoundsTest);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp() override;

    void tearDown() override;

  private:
    enum class CellState : bool {
        Empty = false,
        Filled = true,
    };

    // #### Helpers ####
    void fillRow(int fullRowIdx);
    void fillCol(int fullColIdx);

    /**
     * Checks that the cells at the given coords are empty/filled according to
     * the given expected state.
     */
    bool checkEmptyOrFilled(CellState expectedState,
                            const std::vector<Vec2> &coords);

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
    void receivePenaltyOutOfBoundsTest();

  private:
    BoardPtr pBoard;
};

CPPUNIT_TEST_SUITE_REGISTRATION(BoardTest);
