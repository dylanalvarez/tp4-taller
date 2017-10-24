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
        //CPPUNIT_TEST(fireTowerAttacksOneTimeEveryThreeSecondsTest);
        CPPUNIT_TEST(fireTowerDoesNotChangeObjetiveIfItsAliveTest);
        CPPUNIT_TEST(attackWhenIsInRangeAndStopAttackingWhenIsOutTest);
        CPPUNIT_TEST(whenEnemyIsInRangeOfWaterTowerItAttacksHimTest);
        //CPPUNIT_TEST(waterTowerAttacksOneTimeEveryThreeSecondsTest);
        CPPUNIT_TEST(waterTowerDoesNotChangeObjetiveIfItsAliveTest);
        CPPUNIT_TEST(movingEnemiesAndAddingOthersTest);
        CPPUNIT_TEST(waterTowerReduceEnemySpeedTest);
        CPPUNIT_TEST(waterTowerReduceEnemySpeedDuringTwoSecondsTest);
        CPPUNIT_TEST(whenEnemyIsInRangeOfEarthTowerItAttacksHimTest);
        //CPPUNIT_TEST(earthTowerAttacksOneTimeEveryFiveSecondsTest);
        CPPUNIT_TEST(earthTowerDoesNotChangeObjetiveIfItsAliveTest);
        CPPUNIT_TEST(whenEnemyIsInRangeOfAirTowerItAttacksHimTest);
        //CPPUNIT_TEST(airTowerAttacksOneTimeEveryFiveSecondsTest);
        CPPUNIT_TEST(airTowerDoesNotChangeObjetiveIfItsAliveTest);
        CPPUNIT_TEST(airTowerMovesBackEnemyWhenHitHimTest);
        CPPUNIT_TEST(airTowerHitsFlyingEnemiesHarderTest);
        CPPUNIT_TEST(whenEnemyIsOutOfRangeFireTowerDoesNotAttackHimTest);
        CPPUNIT_TEST(earthTowerCantAttackFlyingUnitsTest);
        CPPUNIT_TEST(addingNotExistingTowerTypeThrowsExceptionTest);
        CPPUNIT_TEST(hittingAnEnemyIncreaseFireTowerExperienceByDealedDamagePointsTest);
        CPPUNIT_TEST(killingEnemyIncreaseTowerExpByDmgDealedPlusFiftyPercentOfEnemyHealthTest);
        CPPUNIT_TEST(cantLevelupWaterTowerWithInsuficientExpPointsTest);
        CPPUNIT_TEST(whenEarthTowerLevelupHisExperienceIsReducedTest);
        CPPUNIT_TEST(ifCantLevelUpHisExperienceItsNotReducedTest);
        CPPUNIT_TEST(levelingTwoTimesDamageOfEarthTowerIncreaseItByTwentyTest);
        CPPUNIT_TEST(levelingImpactRangeOfFiretowerIncreasesItByOnesTest);
        CPPUNIT_TEST(levelingNotExistingAttributeThrowExceptionTest);
        CPPUNIT_TEST(deadEnemiesAreDestroyedTest);
        CPPUNIT_TEST(throwSpellTerraformingCreatesFirmGroundTest);
        CPPUNIT_TEST(cantThrowTerraformingOverPathTest);
        CPPUNIT_TEST(cantThrowTerraformingOverTowerPositionTest);
        CPPUNIT_TEST(onlyEarthPlayerCanThrowTerraformingTest);
        CPPUNIT_TEST(fissureOnlyLastOneSecondTest);
        CPPUNIT_TEST(throwSpellFissureDestroysAllEnemysInPositionTest);
        CPPUNIT_TEST(EnemyPassingThrowFissureDieTest);
        CPPUNIT_TEST(fissureDoesNotAffectFlyingEnemiesTest);
        CPPUNIT_TEST(meteoriteDealsDamageToEnemyHittedTest);
        CPPUNIT_TEST(throwMeteoriteToNotExistingIdThrowsExceptionTest);
        CPPUNIT_TEST(meteoriteHasACooldownTest);
        CPPUNIT_TEST(fireWallDealDamageToEnemiesInTheAreaTest);
        CPPUNIT_TEST(fireWallOnlyLastFiveSecondsTest);
        CPPUNIT_TEST(freezingStopsTheEnemyHittedTest);
        CPPUNIT_TEST(freezingOnlyLastFiveSecondsTets);
        CPPUNIT_TEST(freezingHasACooldownTest);
        CPPUNIT_TEST(blizzardDealsDamageAndSlowDownEnemiesOnAreaTest);
        CPPUNIT_TEST(blizzardHasACooldownTest);
        CPPUNIT_TEST(tornatoDealsDamageToAllEnemiesInTheAreaTest);
        CPPUNIT_TEST(tornatoHasACooldownTest);
        CPPUNIT_TEST(tornatoDoesNotDealDamageToNearbyEnemiesTest);
        CPPUNIT_TEST(rayDealsDamageToTheTargetTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;
    void tearDown() override;

protected:
    /*** Enemies ***/
    void addingGreenDemonAddsGreenDemonEnemyWithHisPropertiesTest();
    void addingAbmonibleAddsAbmonibleEnemyWithHisPropertiesTest();
    void addingBloodyHawkAddsBloodyHawkEnemyWithHisPropertiesTest();
    void addingSpectrumAddsSpectrumEnemyWithHisPropertiesTest();
    void addingGoatManAddsGoatManEnemyWithHisPropertiesTest();
    void addingUndeadAddsUndeadEnemyWithHisPropertiesTest();
    void addingNonExistingEnemyTypeThrowExceptionTest();
    void movingEnemiesOverPathTest();
    void movingEnemiesOverPathWithDistanceBetweenThemTest();
    void movingEnemiesAndAddingOthersTest();
    void deadEnemiesAreDestroyedTest();

    /*** Players ***/
    void ifNotAddedPlayerTriesToAddTowerThrowExceptionTest();
    void addedPlayerCanAddTowerTest();
    void cantAddMoreThanFourPlayersTest();
    void throwSpellTerraformingCreatesFirmGroundTest();
    void cantThrowTerraformingOverPathTest();
    void cantThrowTerraformingOverTowerPositionTest();
    void onlyEarthPlayerCanThrowTerraformingTest();
    void throwSpellFissureDestroysAllEnemysInPositionTest();
    void fissureOnlyLastOneSecondTest();
    void EnemyPassingThrowFissureDieTest();
    void fissureDoesNotAffectFlyingEnemiesTest();
    void meteoriteDealsDamageToEnemyHittedTest();
    void throwMeteoriteToNotExistingIdThrowsExceptionTest();
    void meteoriteHasACooldownTest();
    void fireWallDealDamageToEnemiesInTheAreaTest();
    void fireWallOnlyLastFiveSecondsTest();
    void freezingStopsTheEnemyHittedTest();
    void freezingOnlyLastFiveSecondsTets();
    void freezingHasACooldownTest();
    void blizzardDealsDamageAndSlowDownEnemiesOnAreaTest();
    void blizzardHasACooldownTest();
    void tornatoDealsDamageToAllEnemiesInTheAreaTest();
    void tornatoHasACooldownTest();
    void tornatoDoesNotDealDamageToNearbyEnemiesTest();
    void rayDealsDamageToTheTargetTest();

    /*** Fire Tower ***/
    void whenEnemyIsInRangeOfTowerTheTowerAttacksHimTest();
    void fireTowerAttacksAllnearbyEnemiesWithLessDamageTest();
    void fireTowerDoesNotAttacksEnemiesThatAreNotInRangeTest();
    void fireTowerAttacksOneTimeEveryThreeSecondsTest();
    void fireTowerDoesNotChangeObjetiveIfItsAliveTest();
    void attackWhenIsInRangeAndStopAttackingWhenIsOutTest();
    void whenEnemyIsOutOfRangeFireTowerDoesNotAttackHimTest();
    void hittingAnEnemyIncreaseFireTowerExperienceByDealedDamagePointsTest();
    void levelingImpactRangeOfFiretowerIncreasesItByOnesTest();

    /*** Water Tower ***/
    void whenEnemyIsInRangeOfWaterTowerItAttacksHimTest();
    void waterTowerAttacksOneTimeEveryThreeSecondsTest();
    void waterTowerDoesNotChangeObjetiveIfItsAliveTest();
    void waterTowerReduceEnemySpeedTest();
    void waterTowerReduceEnemySpeedDuringTwoSecondsTest();
    void cantLevelupWaterTowerWithInsuficientExpPointsTest();

    /*** Earth Tower ***/
    void whenEnemyIsInRangeOfEarthTowerItAttacksHimTest();
    void earthTowerAttacksOneTimeEveryFiveSecondsTest();
    void earthTowerDoesNotChangeObjetiveIfItsAliveTest();
    void earthTowerCantAttackFlyingUnitsTest();
    void levelingTwoTimesDamageOfEarthTowerIncreaseItByTwentyTest();
    void whenEarthTowerLevelupHisExperienceIsReducedTest();

    /*** Air Tower ***/
    void whenEnemyIsInRangeOfAirTowerItAttacksHimTest();
    void airTowerAttacksOneTimeEveryFiveSecondsTest();
    void airTowerDoesNotChangeObjetiveIfItsAliveTest();
    void airTowerMovesBackEnemyWhenHitHimTest();
    void airTowerHitsFlyingEnemiesHarderTest();

    /*** Comunes ***/
    void addingNotExistingTowerTypeThrowsExceptionTest();
    void killingEnemyIncreaseTowerExpByDmgDealedPlusFiftyPercentOfEnemyHealthTest();
    void ifCantLevelUpHisExperienceItsNotReducedTest();
    void levelingNotExistingAttributeThrowExceptionTest();

private:
    TowerDefenseGame* game;
};


#endif //TOWERDEFENSE_TOWERDEFENSEGAMETEST_H
