//
// Created by facundo on 10/10/17.
//

#include "PositionTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(PositionTest);

PositionTest::PositionTest() : position(0,0){}

void PositionTest::AddingIntegerToPositionIncrementsBothCoordinatesTest() {
    position += 3;

    CPPUNIT_ASSERT(position.getX() == 3 && position.getY() == 3);
}

void PositionTest::AddingPositionToPositionDoesTheSumTest() {
    Position pos(1,1);

    position += pos;

    CPPUNIT_ASSERT(position.getX() == 1 && position.getY() == 1);
}
