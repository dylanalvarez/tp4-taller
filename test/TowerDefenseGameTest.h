//
// Created by facundo on 16/10/17.
//

#ifndef TOWERDEFENSE_TOWERDEFENSEGAMETEST_H
#define TOWERDEFENSE_TOWERDEFENSEGAMETEST_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/model/TowerDefenseGame.h"

class TowerDefenseGameTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(TowerDefenseGameTest);
        CPPUNIT_TEST(addingGreenDemonAddsGreenDemonEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingAbmonibleAddsAbmonibleEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingBloodyHawkAddsBloodyHawkEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingSpectrumAddsSpectrumEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingGoatManAddsGoatManEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingUndeadAddsUndeadEnemyWithHisPropertiesTest);
        CPPUNIT_TEST(addingNonExistingEnemyTypeThrowExceptionTest);
        CPPUNIT_TEST(movingEnemiesOverPathTest);
        CPPUNIT_TEST(movingEnemiesOverPathWithDistanceBetweenThemTest);
        //CPPUNIT_TEST(towersCanOnlyBePlacedOnFirmGroundTest);
    CPPUNIT_TEST_SUITE_END();

public:
    TowerDefenseGameTest();

protected:
    void addingGreenDemonAddsGreenDemonEnemyWithHisPropertiesTest();
    void addingAbmonibleAddsAbmonibleEnemyWithHisPropertiesTest();
    void addingBloodyHawkAddsBloodyHawkEnemyWithHisPropertiesTest();
    void addingSpectrumAddsSpectrumEnemyWithHisPropertiesTest();
    void addingGoatManAddsGoatManEnemyWithHisPropertiesTest();
    void addingUndeadAddsUndeadEnemyWithHisPropertiesTest();
    void addingNonExistingEnemyTypeThrowExceptionTest();
    void movingEnemiesOverPathTest();
    void movingEnemiesOverPathWithDistanceBetweenThemTest();

private:
    TowerDefenseGame game;
};


#endif //TOWERDEFENSE_TOWERDEFENSEGAMETEST_H
