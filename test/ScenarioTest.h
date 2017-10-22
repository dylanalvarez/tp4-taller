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
        CPPUNIT_TEST(towersCanOnlyBePlacedOnFirmGroundTest);
        CPPUNIT_TEST(cantAddTwoTowersOnTheSamePlaceTest);
    CPPUNIT_TEST_SUITE_END();

public:
    ScenarioTest();
    ~ScenarioTest() override;

protected:
    void getEnemyInRangeTest();
    void getEnemyInRangeReturnsTheEnemyClosestToTheLimitTest();
    void whenTwoEnemiesAreAtTheSameDistanceOfRangeReturnsTheFirtsAddedTest();
    void getEnemyInRangeWhenNoOneIsRetunsAnEmpyListTest();
    void towersCanOnlyBePlacedOnFirmGroundTest();
    void cantAddTwoTowersOnTheSamePlaceTest();
    // TODO testear que un tile no puede ser camino y terreno firme al mismo tiempo
private:
    Scenario* scenario;
};


#endif //TOWERDEFENSE_SCENARIOTEST_H
