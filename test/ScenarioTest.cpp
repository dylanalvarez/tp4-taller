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
    scenario->addEnemy(enemy_id,"green_demon");

    // se obtiene 1 enemigo en el rango especificado
    std::vector<Enemy*> enemies = scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1);

    CPPUNIT_ASSERT_EQUAL(enemy_id, enemies[0]->getID());
}

void ScenarioTest::getEnemyInRangeReturnsTheEnemyClosestToTheLimitTest() {
    int id_1 = 1;
    int id_2 = 2;

    scenario->addEnemy(id_2, "green_demon");
    // se mueve el primer enemigo
    scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1)[0]->move();

    scenario->addEnemy(id_1, "green_demon");

    // se obtiene 1 enemigo en el rango especificado
    std::vector<Enemy*> enemies = scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1);

    CPPUNIT_ASSERT_EQUAL(id_2, enemies[0]->getID());
}

void ScenarioTest::whenTwoEnemiesAreAtTheSameDistanceOfRangeReturnsTheFirtsAddedTest() {
    int id_1 = 1;
    int id_2 = 2;

    scenario->addEnemy(id_1, "green_demon");
    scenario->addEnemy(id_2, "green_demon");

    // se mueve el primer enemigo
    scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1)[0]->move();

    // se obtiene 1 enemigo en el rango especificado
    std::vector<Enemy*> enemies = scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1);

    CPPUNIT_ASSERT_EQUAL(id_1, enemies[0]->getID());
}

void ScenarioTest::getEnemyInRangeWhenNoOneIsRetunsAnEmpyListTest() {
    int id_1 = 1;
    int id_2 = 2;

    scenario->addEnemy(id_1, "green_demon");
    scenario->addEnemy(id_2, "green_demon");

    // se obtiene 1 enemigo en el rango especificado
    std::vector<Enemy*> enemies = scenario->getEnemiesInRange(Range(Vector(0, 5), 2), 1);

    CPPUNIT_ASSERT(enemies.empty());
}
