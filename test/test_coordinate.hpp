#ifndef TEST_COORDINATE_HPP
#define TEST_COORDINATE_HPP

#include "../src/coordinate/coordinate.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CoordinateTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(CoordinateTest);

    CPPUNIT_TEST(assignmentOperatorsTest);

    CPPUNIT_TEST(gettersAndSettersTest);

    CPPUNIT_TEST(equalityOperatorsTest);

    CPPUNIT_TEST(additionTest);
    CPPUNIT_TEST(subtractionTest);
    CPPUNIT_TEST(compoundAdditionTest);
    CPPUNIT_TEST(compoundSubtractionTest);

    CPPUNIT_TEST(moveRowAndColTest);

    CPPUNIT_TEST(outputStreamOperatorTest);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp() override;

    void tearDown() override;

  protected:
    void assignmentOperatorsTest();

    void gettersAndSettersTest();

    void equalityOperatorsTest();

    // arithmetic
    void additionTest();
    void subtractionTest();
    void compoundAdditionTest();
    void compoundSubtractionTest();

    void moveRowAndColTest();

    void outputStreamOperatorTest();

  private:
    Coordinate *coord1, *coord2, *coord3;
};

CPPUNIT_TEST_SUITE_REGISTRATION(CoordinateTest);

#endif
