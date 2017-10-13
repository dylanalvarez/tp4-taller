//
// Created by facundo on 10/10/17.
//

#include "VectorTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);

VectorTest::VectorTest() : vector(0,0) {}

void VectorTest::AddingIntegerToVectorIncrementsBothCoordinatesTest() {
    vector += 3;

    CPPUNIT_ASSERT(vector.getX() == 3 && vector.getY() == 3);
}

void VectorTest::AddingVectorToVectorDoesTheSumTest() {
    Vector pos(1, 1);

    vector += pos;

    CPPUNIT_ASSERT(vector.getX() == 1 && vector.getY() == 1);
}

void VectorTest::vectorMinusVectorReturnTheDifferenceTest() {
    Vector pos(1, 1);

    Vector result = vector - pos;

    CPPUNIT_ASSERT(result.getX() == -1 && result.getY() == -1);
}

void VectorTest::normalizeVectorTest() {
    Vector vec(4,3);

    vec.normalize();

    CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0 / 5.0, vec.getX(), 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0 / 5.0, vec.getY(), 0.01);
}

void VectorTest::twoVectorsAreDifferentIfOneOfTheirCoordinatesAreDifferent() {
    Vector vec1(1,1);
    Vector vec2(1,0);

    CPPUNIT_ASSERT(vec1 != vec2);
}

void VectorTest::twoVectorsAreEqualIfBothOfTheirCoordinatesAreEqual() {
    Vector vec1(1,1);
    Vector vec2(1,1);

    CPPUNIT_ASSERT(vec1 == vec2);
}

void VectorTest::differentVectorsTest() {
    Vector vec1(1,1);
    Vector vec2(1,0);

    CPPUNIT_ASSERT(!(vec1 == vec2));
}

void VectorTest::normalizeAndRoundTest() {
    Vector vec(1,1);

    vec.normalizeAndRound();

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, vec.getX(), 0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, vec.getY(), 0);
}

void VectorTest::vectorPlusVectorReturnTheSumTest() {
    Vector vec(1, 1);
    Vector result = vec + vec;

    CPPUNIT_ASSERT(result.getX() == 2 && result.getY() == 2);
}

void VectorTest::oneVectorIsLargerThanAnotherIfItsNormIs() {
    Vector vec1(5,0);
    Vector vec2(3,0);

    CPPUNIT_ASSERT(vec1 > vec2);
}
