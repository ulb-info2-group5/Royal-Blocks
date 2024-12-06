#include "../src/tetris/tetris.hpp"

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
    Tetris tetris;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TetrisTest);
