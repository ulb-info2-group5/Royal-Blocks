#include "../src/tetromino/tetromino.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>

class TetrominoTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TetrominoTest);
    CPPUNIT_TEST(tetrominoCreationTest);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp() override;

    void tearDown() override;

  protected:
    void tetrominoCreationTest();

  private:
    std::unique_ptr<Tetromino> tetromino_;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TetrominoTest);
