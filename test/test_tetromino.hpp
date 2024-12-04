#include "../src/tetromino/tetromino.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>

class TetrominoTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TetrominoTest);
    CPPUNIT_TEST(shapeTest);
    CPPUNIT_TEST(getWidthAndHeightTest);
    CPPUNIT_TEST(moveTest);
    CPPUNIT_TEST(rotateTest);
    CPPUNIT_TEST(kicksTetrominoOTest);
    CPPUNIT_TEST(kicksTetrominoITest);
    CPPUNIT_TEST(kicksTetrominoLTest);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp() override;

    void tearDown() override;

  protected:
    void shapeTest();
    void getWidthAndHeightTest();
    void moveTest();
    void rotateTest();
    void kicksTetrominoOTest();
    void kicksTetrominoITest();
    void kicksTetrominoLTest();

  private:
    std::vector<std::unique_ptr<Tetromino>> tetrominos;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TetrominoTest);
