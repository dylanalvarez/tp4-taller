#ifndef TOWERDEFENSE_RANGETEST_H
#define TOWERDEFENSE_RANGETEST_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class RangeTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(RangeTest);
        CPPUNIT_TEST(isInRangeReturnsTrueIfVectorIsInRangeTest);
        CPPUNIT_TEST(isInRangeReturnsFalseIfVectorIsNotInRangeTest);
        CPPUNIT_TEST(isInRangeReturnsTrueIfVectorIsInTheLimitOfRangeTest);
    CPPUNIT_TEST_SUITE_END();

protected:
    void isInRangeReturnsTrueIfVectorIsInRangeTest();
    void isInRangeReturnsFalseIfVectorIsNotInRangeTest();
    void isInRangeReturnsTrueIfVectorIsInTheLimitOfRangeTest();
};


#endif //TOWERDEFENSE_RANGETEST_H
