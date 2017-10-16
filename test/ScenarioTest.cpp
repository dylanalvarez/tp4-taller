//
// Created by facundo on 15/10/17.
//

#include "ScenarioTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ScenarioTest);

ScenarioTest::ScenarioTest() {
    Path path({Vector(0,0), Vector(0,5)});
    scenario = new Scenario(std::move(path));
}

ScenarioTest::~ScenarioTest() {
    delete scenario;
}

void ScenarioTest::getEnemyInRangeTest() {
    int enemy_id = 1;
    Enemy enemy(enemy_id, scenario->getPath(), 100, 1, false);
    scenario->addEnemy(std::move(enemy));

    // se obtiene 1 enemigo en el rango especificado
    std::vector<Enemy*> enemies = scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1);

    CPPUNIT_ASSERT_EQUAL(1, (int)enemies.size());
    CPPUNIT_ASSERT_EQUAL(enemy_id, enemies[0]->getID());
}

void ScenarioTest::getEnemyInRangeReturnsTheEnemyClosestToTheLimitTest() {
    int id_1 = 1;
    int id_2 = 2;
    Enemy enemy1(id_1, scenario->getPath(), 100, 1, false);
    Enemy enemy2(id_2, scenario->getPath(), 100, 1, false);

    scenario->addEnemy(std::move(enemy2));
    // se mueve el primer enemigo
    scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1)[0]->move();

    scenario->addEnemy(std::move(enemy1));

    // se obtiene 1 enemigo en el rango especificado
    std::vector<Enemy*> enemies = scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1);

    CPPUNIT_ASSERT_EQUAL(1, (int)enemies.size());
    CPPUNIT_ASSERT_EQUAL(id_2, enemies[0]->getID());
}

void ScenarioTest::whenTwoEnemiesAreAtTheSameDistanceOfRangeReturnsTheFirtsAddedTest() {
    int id_1 = 1;
    int id_2 = 2;
    Enemy enemy1(id_1, scenario->getPath(), 100, 1, false);
    Enemy enemy2(id_2, scenario->getPath(), 100, 1, false);

    scenario->addEnemy(std::move(enemy2));
    scenario->addEnemy(std::move(enemy1));

    // se mueve el primer enemigo
    scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1)[0]->move();

    // se obtiene 1 enemigo en el rango especificado
    std::vector<Enemy*> enemies = scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1);

    CPPUNIT_ASSERT_EQUAL(1, (int)enemies.size());
    CPPUNIT_ASSERT_EQUAL(id_2, enemies[0]->getID());
}

void ScenarioTest::getEnemyInRangeWhenNoOneIsRetunsAnEmpyListTest() {
    int id_1 = 1;
    int id_2 = 2;
    Enemy enemy1(id_1, scenario->getPath(), 100, 1, false);
    Enemy enemy2(id_2, scenario->getPath(), 100, 1, false);

    scenario->addEnemy(std::move(enemy2));
    scenario->addEnemy(std::move(enemy1));

    // se obtiene 1 enemigo en el rango especificado
    std::vector<Enemy*> enemies = scenario->getEnemiesInRange(Range(Vector(0, 5), 2), 1);

    CPPUNIT_ASSERT(enemies.empty());
}
