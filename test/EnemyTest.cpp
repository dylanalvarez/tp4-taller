//
// Created by facundo on 13/10/17.
//

#include "EnemyTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(EnemyTest);

void EnemyTest::moveEnemyMovesItOneCoordinateInTheDirectionOfNextPositionTest() {
    Vector pos1(0,0);
    Vector pos2(3,0);
    std::vector<Vector> positions = {pos1, pos2};
    Path path(positions);

    // hp = 10, speed = 1, cant flight
    enemy = new Enemy(path, 10, 1, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 1  && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 2  && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 3  && current_pos.getY() == 0);

    delete enemy;
}

void EnemyTest::enemyStartsOnInitialPositionOfPathTest() {
    Vector pos1(1,1);
    Vector pos2(5,0);
    std::vector<Vector> positions = {pos1, pos2};
    Path path(positions);

    // hp = 10, speed = 1, cant flight
    enemy = new Enemy(path, 10, 1, false);

    CPPUNIT_ASSERT(enemy->getCurrentPosition().getX() == 1 &&
                           enemy->getCurrentPosition().getY() == 1);

    delete enemy;
}

void EnemyTest::movementInTwoDirectionsTest() {
    Vector pos1(0, 0);
    Vector pos2(2, 0);
    Vector pos3(2, 2);
    std::vector<Vector> positions = {pos1, pos2, pos3};
    Path path(positions);

    // hp = 10, speed = 1, cant flight
    enemy = new Enemy(path, 10, 1, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 1  && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 2  && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 2  && current_pos.getY() == 1);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 2  && current_pos.getY() == 2);

    delete enemy;
}

void EnemyTest::diagonalMovementTest() {
    Vector pos1(0, 0);
    Vector pos2(2, 2);
    std::vector<Vector> positions = {pos1, pos2};
    Path path(positions);

    // hp = 10, speed = 1, cant flight
    enemy = new Enemy(path, 10, 1, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 1);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 2  && current_pos.getY() == 2);

    delete enemy;
}

void EnemyTest::speedIncrementTheNumberOfCoordinatesThanEnemyMoves() {
    Vector pos1(0, 0);
    Vector pos2(0, 4);
    std::vector<Vector> positions = {pos1, pos2};
    Path path(positions);

    // hp = 10, speed = 2, cant flight
    enemy = new Enemy(path, 10, 2, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 0 && current_pos.getY() == 2);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 0  && current_pos.getY() == 4);

    delete enemy;
}

void EnemyTest::ifSpeedIsTwoAndOnlyOneCoordinateRemainsEnemyMovesOneCoordinate() {
    Vector pos1(0, 0);
    Vector pos2(0, 5);
    std::vector<Vector> positions = {pos1, pos2};
    Path path(positions);

    // hp = 10, speed = 2, cant flight
    enemy = new Enemy(path, 10, 2, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 0 && current_pos.getY() == 2);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 0  && current_pos.getY() == 4);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 0  && current_pos.getY() == 5);

    delete enemy;
}
