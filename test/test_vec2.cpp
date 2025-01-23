#include "./test_vec2.hpp"

#include "./../src/vec2/vec2.hpp"

#include <cppunit/TestAssert.h>

void Vec2Test::setUp() {
    vec12 = {1, 2};
    vec23 = {2, 3};
    vec45 = {4, 5};
    vec68 = {6, 8};
}

void Vec2Test::tearDown() {}

void Vec2Test::assignmentOperatorsTest() {
    vec45 = vec23;
    CPPUNIT_ASSERT_EQUAL(vec23.getX(), vec45.getX());
    CPPUNIT_ASSERT_EQUAL(vec23.getY(), vec45.getY());

    vec12 = std::move(vec45);
    CPPUNIT_ASSERT_EQUAL(4, vec12.getX());
    CPPUNIT_ASSERT_EQUAL(5, vec12.getY());
}

void Vec2Test::gettersAndSettersTest() {
    vec23.setX(9);
    CPPUNIT_ASSERT_EQUAL(9, vec23.getX());
    CPPUNIT_ASSERT_EQUAL(3, vec23.getY());

    vec45.setY(2);
    CPPUNIT_ASSERT_EQUAL(4, vec45.getX());
    CPPUNIT_ASSERT_EQUAL(2, vec45.getY());
}

void Vec2Test::equalityOperatorsTest() {
    CPPUNIT_ASSERT(vec12 != vec23);
    CPPUNIT_ASSERT(vec23 != vec45);

    vec12 = vec23;
    CPPUNIT_ASSERT(vec12 == vec12);
    CPPUNIT_ASSERT(!(vec12 == vec45));
}

void Vec2Test::additionTest() {
    Vec2 result{vec12 + vec23};
    CPPUNIT_ASSERT_EQUAL(Vec2(3, 5), result);
}

void Vec2Test::subtractionTest() {
    Vec2 result{vec68 - vec12};
    CPPUNIT_ASSERT_EQUAL(Vec2(5, 6), result);
}

void Vec2Test::compoundAdditionTest() {
    vec12 += vec23;
    CPPUNIT_ASSERT_EQUAL(Vec2(3, 5), vec12);
}

void Vec2Test::compoundSubtractionTest() {
    vec68 -= vec12;
    CPPUNIT_ASSERT_EQUAL(Vec2(5, 6), vec68);
}

void Vec2Test::moveTest() {
    vec12.moveX(2);
    CPPUNIT_ASSERT_EQUAL(Vec2(3, 2), vec12);

    vec45.moveX(-2);
    CPPUNIT_ASSERT_EQUAL(Vec2(2, 5), vec45);

    vec45.moveX(2);
    CPPUNIT_ASSERT_EQUAL(Vec2(4, 7), vec45);

    vec68.moveY(-2);
    CPPUNIT_ASSERT_EQUAL(Vec2(6, 6), vec68);
}

void Vec2Test::rotateAroundTest() {
    vec45.rotateAround(vec68, true);
    CPPUNIT_ASSERT_EQUAL(Vec2(3, 10), vec45);
    vec45.rotateAround(vec68, true);
    CPPUNIT_ASSERT_EQUAL(Vec2(8, 11), vec45);
    vec45.rotateAround(vec68, true);
    CPPUNIT_ASSERT_EQUAL(Vec2(9, 6), vec45);
    vec45.rotateAround(vec68, true);
    CPPUNIT_ASSERT_EQUAL(Vec2(4, 5), vec45);
}

void Vec2Test::outputStreamOperatorTest() {
    std::ostringstream oss;
    oss << vec68;
    CPPUNIT_ASSERT_EQUAL(std::string("(6, 8)"), oss.str());
}
