//
// Created by facundo on 13/10/17.
//

#include "EnemyTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(EnemyTest);

void EnemyTest::moveEnemyMovesItOneCoordinateInTheDirectionOfNextPositionTest() {
    Vector pos1(0,0);
    Vector pos2(3,0);
    std::vector<Vector> positions = {pos1, pos2};
    Path path(std::move(positions));

    // hp = 10, speed = 1, cant flight
    // se multiplica la velocidad por una base_speed de 4 y
    // una base_speed_reduction de 0.125 por motivos de ajuste grafico
    // entonces 2 * 4 * 0.125 = 1
    enemy = new Enemy(path, 10, 2, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 2 && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 3 && current_pos.getY() == 0);

    delete enemy;
}

void EnemyTest::enemyStartsOnInitialPositionOfPathTest() {
    Vector pos1(1,1);
    Vector pos2(5,0);
    std::vector<Vector> positions = {pos1, pos2};
    Path path(std::move(positions));

    // hp = 10, speed = 1, cant flight
    // se multiplica la velocidad por una base_speed de 4 y
    // una base_speed_reduction de 0.125 por motivos de ajuste grafico
    // entonces 2 * 4 * 0.125 = 1
    enemy = new Enemy(path, 10, 2, false);

    CPPUNIT_ASSERT(enemy->getCurrentPosition().getX() == 1 &&
                           enemy->getCurrentPosition().getY() == 1);

    delete enemy;
}

void EnemyTest::movementInTwoDirectionsTest() {
    Vector pos1(0, 0);
    Vector pos2(2, 0);
    Vector pos3(2, 2);
    std::vector<Vector> positions = {pos1, pos2, pos3};
    Path path(std::move(positions));

    // hp = 10, speed = 1, cant flight
    // se multiplica la velocidad por una base_speed de 4 y
    // una base_speed_reduction de 0.125 por motivos de ajuste grafico
    // entonces 2 * 4 * 0.125 = 1
    enemy = new Enemy(path, 10, 2, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 2 && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 2 && current_pos.getY() == 1);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 2 && current_pos.getY() == 2);

    delete enemy;
}

void EnemyTest::diagonalMovementTest() {
    Vector pos1(0, 0);
    Vector pos2(2, 2);
    std::vector<Vector> positions = {pos1, pos2};
    Path path(std::move(positions));

    // hp = 10, speed = 1, cant flight
    // se multiplica la velocidad por una base_speed de 4 y
    // una base_speed_reduction de 0.125 por motivos de ajuste grafico
    // entonces 2 * 4 * 0.125 = 1
    enemy = new Enemy(path, 10, 2, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 1);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 2 && current_pos.getY() == 2);

    delete enemy;
}

void EnemyTest::speedIncrementTheNumberOfCoordinatesThanEnemyMovesTest() {
    Vector pos1(0, 0);
    Vector pos2(0, 4);
    std::vector<Vector> positions = {pos1, pos2};
    Path path(std::move(positions));

    // hp = 10, speed = 2, cant flight
    // se multiplica la velocidad por una base_speed de 4 y
    // una base_speed_reduction de 0.125 por motivos de ajuste grafico
    // entonces 4 * 4 * 0.125 = 2
    enemy = new Enemy(path, 10, 4, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 0 && current_pos.getY() == 2);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 0 && current_pos.getY() == 4);

    delete enemy;
}

void EnemyTest::ifSpeedIsTwoAndOnlyOneCoordinateRemainsEnemyMovesOneCoordinateTest() {
    Vector pos1(0, 0);
    Vector pos2(0, 5);
    std::vector<Vector> positions = {pos1, pos2};
    Path path(std::move(positions));

    // hp = 10, speed = 2, cant flight
    // se multiplica la velocidad por una base_speed de 4 y
    // una base_speed_reduction de 0.125 por motivos de ajuste grafico
    // entonces 4 * 4 * 0.125 = 2
    enemy = new Enemy(path, 10, 4, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 0 && current_pos.getY() == 2);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 0 && current_pos.getY() == 4);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 0 && current_pos.getY() == 5);

    delete enemy;
}

void EnemyTest::movementOverCompletePathTest() {
    Vector pos1(1, 5);
    Vector pos2(1, 3);
    Vector pos3(3, 3);
    Vector pos4(4, 3);
    Vector pos5(4, 1);
    std::vector<Vector> positions = {pos1, pos2, pos3, pos4, pos5};
    Path path(std::move(positions));

    // hp = 10, speed = 2, cant flight
    // se multiplica la velocidad por una base_speed de 4 y
    // una base_speed_reduction de 0.125 por motivos de ajuste grafico
    // entonces 4 * 4 * 0.125 = 2
    enemy = new Enemy(path, 10, 4, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 3);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 3 && current_pos.getY() == 3);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 4 && current_pos.getY() == 2);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 4 && current_pos.getY() == 1);

    delete enemy;
}

void EnemyTest::movementWhenInitialPositionIsCloseToEndingPositonTest() {
    Vector pos1(1, 4);
    Vector pos2(1, 2);
    Vector pos3(1, 0);
    Vector pos4(3, 0);
    Vector pos5(3, 2);
    Vector pos6(5, 2);
    Vector pos7(5, 4);
    Vector pos8(3, 4);
    std::vector<Vector> positions = {pos1, pos2, pos3, pos4,
                                     pos5, pos6, pos7, pos8};
    Path path(std::move(positions));

    // hp = 10, speed = 3, cant flight
    // se multiplica la velocidad por una base_speed de 4 y
    // una base_speed_reduction de 0.125 por motivos de ajuste grafico
    // entonces 6 * 4 * 0.125 = 3
    enemy = new Enemy(path, 10, 6, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 1);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 3 && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 4 && current_pos.getY() == 2);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 5 && current_pos.getY() == 4);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 3 && current_pos.getY() == 4);

    delete enemy;
}

void EnemyTest::movementWhenInitialPositionIsEqualToEndingPositonTest() {
    Vector pos1(1, 4);
    Vector pos2(1, 2);
    Vector pos3(1, 0);
    Vector pos4(3, 0);
    Vector pos5(3, 2);
    Vector pos6(5, 2);
    Vector pos7(5, 4);
    Vector pos8(3, 4);
    Vector pos9(1, 4);
    std::vector<Vector> positions = {pos1, pos2, pos3, pos4,
                                     pos5, pos6, pos7, pos8, pos9};
    Path path(std::move(positions));

    // hp = 10, speed = 2, cant flight
    // se multiplica la velocidad por una base_speed de 4 y
    // una base_speed_reduction de 0.125 por motivos de ajuste grafico
    // entonces 4 * 4 * 0.125 = 2
    enemy = new Enemy(path, 10, 4, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 2);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 3 && current_pos.getY() == 0);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 3 && current_pos.getY() == 2);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 5 && current_pos.getY() == 2);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 5 && current_pos.getY() == 4);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 3 && current_pos.getY() == 4);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 4);

    delete enemy;
}

void EnemyTest::whenPathConsistOnlyOfOnePointEnemyDoesNotMoveTest() {
    Vector pos1(1, 4);

    std::vector<Vector> positions = {pos1};
    Path path(std::move(positions));

    // hp = 10, speed = 3, cant flight
    // se multiplica la velocidad por una base_speed de 4 y
    // una base_speed_reduction de 0.125 por motivos de ajuste grafico
    // entonces 6 * 4 * 0.125 = 3
    enemy = new Enemy(path, 10, 6, false);

    enemy->move();
    const Vector& current_pos = enemy->getCurrentPosition();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 4);

    enemy->move();
    CPPUNIT_ASSERT(current_pos.getX() == 1 && current_pos.getY() == 4);

    delete enemy;
}
