//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_POSITIONTEST_H
#define TOWERDEFENSE_POSITIONTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/model/Position.h"

class PositionTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(PositionTest);
        CPPUNIT_TEST(AddingIntegerToPositionIncrementsBothCoordinatesTest);
        CPPUNIT_TEST(AddingPositionToPositionDoesTheSumTest);
    CPPUNIT_TEST_SUITE_END();

public:
    PositionTest();

protected:
    void AddingIntegerToPositionIncrementsBothCoordinatesTest();
    void AddingPositionToPositionDoesTheSumTest();

private:
    Position position;
};


#endif //TOWERDEFENSE_POSITIONTEST_H
