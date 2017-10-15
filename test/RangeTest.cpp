//
// Created by facundo on 15/10/17.
//

#include "RangeTest.h"
#include "../src/model/Range.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RangeTest);

void RangeTest::isInRangeReturnsTrueIfVectorIsInRangeTest() {
    Vector origin(0,0);
    // centro = (0,0), radio = 3
    Range range(origin, 3);
    Vector vector(0,2);

    CPPUNIT_ASSERT(range.isInRange(vector));
}

void RangeTest::isInRangeReturnsFalseIfVectorIsNotInRangeTest() {
    Vector origin(0,0);
    // centro = (0,0), radio = 3
    Range range(origin, 3);
    Vector vector(0,4);

    CPPUNIT_ASSERT(!range.isInRange(vector));
}

void RangeTest::isInRangeReturnsTrueIfVectorIsInTheLimitOfRangeTest() {
    Vector origin(0,0);
    // centro = (0,0), radio = 3
    Range range(origin, 3);
    Vector vector(0,3);

    CPPUNIT_ASSERT(range.isInRange(vector));
}
