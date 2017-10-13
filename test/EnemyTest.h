//
// Created by facundo on 13/10/17.
//

#ifndef TOWERDEFENSE_ENEMYTEST_H
#define TOWERDEFENSE_ENEMYTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/model/Enemy.h"

class EnemyTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(EnemyTest);
        CPPUNIT_TEST(moveEnemyMovesItOneCoordinateInTheDirectionOfNextPositionTest);
        CPPUNIT_TEST(enemyStartsOnInitialPositionOfPathTest);
        CPPUNIT_TEST(movementInTwoDirectionsTest);
        CPPUNIT_TEST(diagonalMovementTest);
        CPPUNIT_TEST(speedIncrementTheNumberOfCoordinatesThanEnemyMoves);
        CPPUNIT_TEST(ifSpeedIsTwoAndOnlyOneCoordinateRemainsEnemyMovesOneCoordinate);
    CPPUNIT_TEST_SUITE_END();

protected:
    void moveEnemyMovesItOneCoordinateInTheDirectionOfNextPositionTest();
    void enemyStartsOnInitialPositionOfPathTest();
    void movementInTwoDirectionsTest();
    void diagonalMovementTest();
    void speedIncrementTheNumberOfCoordinatesThanEnemyMoves();
    void ifSpeedIsTwoAndOnlyOneCoordinateRemainsEnemyMovesOneCoordinate();
private:
    Enemy* enemy = nullptr;
};


#endif //TOWERDEFENSE_ENEMYTEST_H
