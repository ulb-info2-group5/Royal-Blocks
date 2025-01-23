#include "../src/tetromino/tetromino.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TetrominoTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TetrominoTest);
    CPPUNIT_TEST(shapeTest);
    CPPUNIT_TEST(getWidthAndHeightTest);
    CPPUNIT_TEST(moveTest);
    CPPUNIT_TEST(rotateTest);
    CPPUNIT_TEST(offset1TetrominoOTest);
    CPPUNIT_TEST(offset1TetrominoITest);
    CPPUNIT_TEST(offset1TetrominoLTest);
    CPPUNIT_TEST(variousOffsetsTetrominoLTest);
    CPPUNIT_TEST(variousOffsetsTetrominoITest);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp() override;

    void tearDown() override;

  protected:
    void shapeTest();
    void getWidthAndHeightTest();
    void moveTest();
    void rotateTest();
    void offset1TetrominoOTest();
    void offset1TetrominoITest();
    void offset1TetrominoLTest();
    void variousOffsetsTetrominoLTest();
    void variousOffsetsTetrominoITest();

  private:
    TetrominoPtr pTetrominoZ;
    TetrominoPtr pTetrominoL;
    TetrominoPtr pTetrominoO;
    TetrominoPtr pTetrominoS;
    TetrominoPtr pTetrominoI;
    TetrominoPtr pTetrominoJ;
    TetrominoPtr pTetrominoT;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TetrominoTest);
