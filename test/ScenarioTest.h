//
// Created by facundo on 15/10/17.
//

#ifndef TOWERDEFENSE_SCENARIOTEST_H
#define TOWERDEFENSE_SCENARIOTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/model/Scenario.h"

class ScenarioTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(ScenarioTest);
        CPPUNIT_TEST(getEnemyInRangeTest);
        CPPUNIT_TEST(getEnemyInRangeReturnsTheEnemyClosestToTheLimitTest);
        CPPUNIT_TEST(whenTwoEnemiesAreAtTheSameDistanceOfRangeReturnsTheFirtsAddedTest);
        CPPUNIT_TEST(getEnemyInRangeWhenNoOneIsRetunsAnEmpyListTest);
        CPPUNIT_TEST(addingGreenDemonAddsGreenDemonEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingAbmonibleAddsAbmonibleEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingBloodyHawkAddsBloodyHawkEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingSpectrumAddsSpectrumEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingGoatManAddsGoatManEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingUndeadAddsUndeadEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingNonExistingEnemyTypeThrowExceptionTest);
        CPPUNIT_TEST(addTwoEnemiesWithSameIdThrowExceptionTest);
        CPPUNIT_TEST(movingEnemiesOverPathTest);
        CPPUNIT_TEST(movingEnemiesOverPathWithDistanceBetweenThemTest);
        CPPUNIT_TEST(movingEnemiesOverCurvedPathTest);
    CPPUNIT_TEST_SUITE_END();

public:
    ScenarioTest();
    ~ScenarioTest() override;

protected:
    void getEnemyInRangeTest();
    void getEnemyInRangeReturnsTheEnemyClosestToTheLimitTest();
    void whenTwoEnemiesAreAtTheSameDistanceOfRangeReturnsTheFirtsAddedTest();
    void getEnemyInRangeWhenNoOneIsRetunsAnEmpyListTest();
    void addingGreenDemonAddsGreenDemonEnemyWithHisPropertiesTest();
    void addingAbmonibleAddsAbmonibleEnemyWithHisPropertiesTest();
    void addingBloodyHawkAddsBloodyHawkEnemyWithHisPropertiesTest();
    void addingSpectrumAddsSpectrumEnemyWithHisPropertiesTest();
    void addingGoatManAddsGoatManEnemyWithHisPropertiesTest();
    void addingUndeadAddsUndeadEnemyWithHisPropertiesTest();
    void addingNonExistingEnemyTypeThrowExceptionTest();
    void addTwoEnemiesWithSameIdThrowExceptionTest();
    void movingEnemiesOverPathTest();
    void movingEnemiesOverPathWithDistanceBetweenThemTest();
    void movingEnemiesOverCurvedPathTest();
private:
    Scenario* scenario;
};


#endif //TOWERDEFENSE_SCENARIOTEST_H
