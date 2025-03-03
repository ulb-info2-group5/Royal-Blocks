#ifndef TEST_VEC2_HPP
#define TEST_VEC2_HPP

#include "vec2/vec2.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Vec2Test : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(Vec2Test);

    CPPUNIT_TEST(assignmentOperatorsTest);

    CPPUNIT_TEST(gettersAndSettersTest);

    CPPUNIT_TEST(equalityOperatorsTest);

    CPPUNIT_TEST(additionTest);
    CPPUNIT_TEST(subtractionTest);
    CPPUNIT_TEST(compoundAdditionTest);
    CPPUNIT_TEST(compoundSubtractionTest);

    CPPUNIT_TEST(moveTest);
    CPPUNIT_TEST(rotateAroundTest);

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

    void moveTest();

    void rotateAroundTest();

    void outputStreamOperatorTest();

  private:
    Vec2 vec12, vec23, vec45, vec68;
};

CPPUNIT_TEST_SUITE_REGISTRATION(Vec2Test);

#endif // TEST_VEC2_HPP
