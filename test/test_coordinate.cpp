#include "./test_coordinate.hpp"

#include "../src/coordinate/coordinate.hpp"
#include <cppunit/TestAssert.h>

void CoordinateTest::setUp() {
    coord1 = new Coordinate{1, 2};
    coord2 = new Coordinate{2, 3};
    coord3 = new Coordinate{2, 6};
}

void CoordinateTest::tearDown() {
    delete coord1;
    delete coord2;
    delete coord3;
}

void CoordinateTest::assignmentOperatorsTest() {
    *coord3 = *coord2;
    CPPUNIT_ASSERT_EQUAL(coord2->getRow(), coord3->getRow());
    CPPUNIT_ASSERT_EQUAL(coord2->getCol(), coord3->getCol());

    *coord1 = std::move(*coord1);
    CPPUNIT_ASSERT_EQUAL(1, coord1->getRow());
    CPPUNIT_ASSERT_EQUAL(2, coord1->getCol());
}

void CoordinateTest::gettersAndSettersTest() {
    coord1->setRow(2);
    coord1->setCol(3);
    CPPUNIT_ASSERT_EQUAL(2, coord1->getRow());
    CPPUNIT_ASSERT_EQUAL(3, coord1->getCol());
}

void CoordinateTest::equalityOperatorsTest() {
    CPPUNIT_ASSERT(*coord1 != *coord2);
    CPPUNIT_ASSERT(*coord2 != *coord3);

    *coord3 = *coord2;
    CPPUNIT_ASSERT(*coord3 == *coord2);
    CPPUNIT_ASSERT(!(*coord1 == *coord2));
}

void CoordinateTest::moveRowAndColTest() {
    // moving coord1 (row)
    coord1->moveRow(3);
    CPPUNIT_ASSERT_EQUAL(Coordinate(4, 2), *coord1);

    coord1->moveRow(-2);
    CPPUNIT_ASSERT_EQUAL(Coordinate(2, 2), *coord1);

    // moving coord2 (col)
    coord2->moveCol(5);
    CPPUNIT_ASSERT_EQUAL(Coordinate(2, 8), *coord2);

    coord2->moveCol(-3);
    CPPUNIT_ASSERT_EQUAL(Coordinate(2, 5), *coord2);
}

void CoordinateTest::additionTest() {
    Coordinate result = *coord1 + *coord2;
    CPPUNIT_ASSERT_EQUAL(Coordinate(3, 5), result);
}

void CoordinateTest::subtractionTest() {
    Coordinate result = *coord2 - *coord1;
    CPPUNIT_ASSERT_EQUAL(Coordinate(1, 1), result);
}

void CoordinateTest::compoundAdditionTest() {
    *coord1 += *coord3;
    CPPUNIT_ASSERT_EQUAL(Coordinate(3, 8), *coord1);
}

void CoordinateTest::compoundSubtractionTest() {
    *coord3 -= *coord2;
    CPPUNIT_ASSERT_EQUAL(Coordinate(0, 3), *coord3);
}

void CoordinateTest::outputStreamOperatorTest() {
    std::ostringstream oss;
    oss << *coord1;
    CPPUNIT_ASSERT_EQUAL(std::string("(1, 2)"), oss.str());
}
