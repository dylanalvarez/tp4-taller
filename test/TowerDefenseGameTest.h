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
        CPPUNIT_TEST(ifNotAddedPlayerTriesToAddTowerThrowExceptionTest);
        CPPUNIT_TEST(addedPlayerCanAddTowerTest);
        CPPUNIT_TEST(whenEnemyIsInRangeOfTowerTheTowerAttacksHimTest);
        CPPUNIT_TEST(cantAddMoreThanFourPlayersTest);
        CPPUNIT_TEST(fireTowerAttacksAllnearbyEnemiesWithLessDamageTest);
        CPPUNIT_TEST(fireTowerDoesNotAttacksEnemiesThatAreNotInRangeTest);
        CPPUNIT_TEST(fireTowerAttacksOneTimeEveryThreeSecondsTest);
        CPPUNIT_TEST(fireTowerDoesNotChangeObjetiveIfItsAliveTest);
        CPPUNIT_TEST(attackWhenIsInRangeAndStopAttackingWhenIsOutTest);
        CPPUNIT_TEST(whenEnemyIsInRangeOfWaterTowerItAttacksHimTest);
        CPPUNIT_TEST(waterTowerAttacksOneTimeEveryThreeSecondsTest);
        CPPUNIT_TEST(waterTowerDoesNotChangeObjetiveIfItsAliveTest);
        CPPUNIT_TEST(movingEnemiesAndAddingOthersTest);
        CPPUNIT_TEST(waterTowerReduceEnemySpeedTest);
        CPPUNIT_TEST(waterTowerReduceEnemySpeedDuringTwoSecondsTest);
        CPPUNIT_TEST(whenEnemyIsInRangeOfEarthTowerItAttacksHimTest);
        CPPUNIT_TEST(earthTowerAttacksOneTimeEveryFiveSecondsTest);
        CPPUNIT_TEST(earthTowerDoesNotChangeObjetiveIfItsAliveTest);
        CPPUNIT_TEST(whenEnemyIsInRangeOfAirTowerItAttacksHimTest);
        CPPUNIT_TEST(airTowerAttacksOneTimeEveryFiveSecondsTest);
        CPPUNIT_TEST(airTowerDoesNotChangeObjetiveIfItsAliveTest);
        CPPUNIT_TEST(airTowerMovesBackEnemyWhenHitHimTest);
        CPPUNIT_TEST(airTowerHitsFlyingEnemiesHarderTest);
        CPPUNIT_TEST(whenEnemyIsOutOfRangeFireTowerDoesNotAttackHimTest);
        CPPUNIT_TEST(earthTowerCantAttackFlyingUnitsTest);
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
    void ifNotAddedPlayerTriesToAddTowerThrowExceptionTest();
    void addedPlayerCanAddTowerTest();
    void cantAddMoreThanFourPlayersTest();
    void whenEnemyIsInRangeOfTowerTheTowerAttacksHimTest();
    void fireTowerAttacksAllnearbyEnemiesWithLessDamageTest();
    void fireTowerDoesNotAttacksEnemiesThatAreNotInRangeTest();
    void fireTowerAttacksOneTimeEveryThreeSecondsTest();
    void fireTowerDoesNotChangeObjetiveIfItsAliveTest();
    void attackWhenIsInRangeAndStopAttackingWhenIsOutTest();
    void whenEnemyIsInRangeOfWaterTowerItAttacksHimTest();
    void waterTowerAttacksOneTimeEveryThreeSecondsTest();
    void waterTowerDoesNotChangeObjetiveIfItsAliveTest();
    void movingEnemiesAndAddingOthersTest();
    void waterTowerReduceEnemySpeedTest();
    void waterTowerReduceEnemySpeedDuringTwoSecondsTest();
    void whenEnemyIsInRangeOfEarthTowerItAttacksHimTest();
    void earthTowerAttacksOneTimeEveryFiveSecondsTest();
    void earthTowerDoesNotChangeObjetiveIfItsAliveTest();
    void whenEnemyIsInRangeOfAirTowerItAttacksHimTest();
    void airTowerAttacksOneTimeEveryFiveSecondsTest();
    void airTowerDoesNotChangeObjetiveIfItsAliveTest();
    void airTowerMovesBackEnemyWhenHitHimTest();
    void airTowerHitsFlyingEnemiesHarderTest();
    void whenEnemyIsOutOfRangeFireTowerDoesNotAttackHimTest();
    void earthTowerCantAttackFlyingUnitsTest();

private:
    TowerDefenseGame game;
};


#endif //TOWERDEFENSE_TOWERDEFENSEGAMETEST_H
