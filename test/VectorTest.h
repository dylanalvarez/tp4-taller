#ifndef TOWERDEFENSE_POSITIONTEST_H
#define TOWERDEFENSE_POSITIONTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/model/Vector.h"

class VectorTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(VectorTest);
        CPPUNIT_TEST(AddingIntegerToVectorIncrementsBothCoordinatesTest);
        CPPUNIT_TEST(AddingVectorToVectorDoesTheSumTest);
        CPPUNIT_TEST(vectorMinusVectorReturnTheDifferenceTest);
        CPPUNIT_TEST(normalizeVectorTest);
        CPPUNIT_TEST(twoVectorsAreDifferentIfOneOfTheirCoordinatesAreDifferent);
        CPPUNIT_TEST(twoVectorsAreEqualIfBothOfTheirCoordinatesAreEqual);
        CPPUNIT_TEST(differentVectorsTest);
        CPPUNIT_TEST(normalizeAndRoundTest);
        CPPUNIT_TEST(vectorPlusVectorReturnTheSumTest);
        CPPUNIT_TEST(oneVectorIsLargerThanAnotherIfItsNormIs);
        CPPUNIT_TEST(normalizeAndRoundWhenBothCordinatesAreZeroDoesNothingTest);
    CPPUNIT_TEST_SUITE_END();

public:
    VectorTest();

protected:
    void AddingIntegerToVectorIncrementsBothCoordinatesTest();
    void AddingVectorToVectorDoesTheSumTest();
    void vectorMinusVectorReturnTheDifferenceTest();
    void normalizeVectorTest();
    void normalizeAndRoundTest();
    void twoVectorsAreDifferentIfOneOfTheirCoordinatesAreDifferent();
    void twoVectorsAreEqualIfBothOfTheirCoordinatesAreEqual();
    void differentVectorsTest();
    void vectorPlusVectorReturnTheSumTest();
    void oneVectorIsLargerThanAnotherIfItsNormIs();
    void normalizeAndRoundWhenBothCordinatesAreZeroDoesNothingTest();

private:
    Vector vector;
};


#endif //TOWERDEFENSE_POSITIONTEST_H
