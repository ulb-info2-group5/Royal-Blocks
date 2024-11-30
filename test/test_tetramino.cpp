#include "../src/coordinate/coordinate.hpp"
#include "../src/tetromino/tetromino.hpp"
#include "../src/tetromino/tetromino_shapes.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>

class TetrominoTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TetrominoTest);
    CPPUNIT_TEST(tetrominoCreationTest);
    // CPPUNIT_TEST(testTetrominoRotation);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp() {
        tetromino_ =
            Tetromino::makeTetromino(TetrominoShape::I, Coordinate(0, 0));
    }

    void tearDown() {}

  protected:
    void tetrominoCreationTest() {
        CPPUNIT_ASSERT(tetromino_ != nullptr);

        CPPUNIT_ASSERT_EQUAL(tetromino_->getAnchorPoint(), Coordinate(0, 0));
    }

  private:
    std::unique_ptr<Tetromino> tetromino_;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TetrominoTest);
