//
// Created by facundo on 15/10/17.
//

#include "ScenarioTest.h"
#include "../src/model/Towers/FireTower.h"
#include "../src/model/Exceptions/TowerError.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ScenarioTest);

ScenarioTest::ScenarioTest() {
    Path path({Vector(0,0), Vector(0,5)});
    scenario = new Scenario(std::move(path), {Vector(1,3)});
}

ScenarioTest::~ScenarioTest() {
    delete scenario;
}

void ScenarioTest::getEnemyInRangeTest() {
    int enemy_id = 1;
    Enemy enemy(enemy_id, scenario->getPath(), 100, 1, false);
    scenario->addEnemy(enemy);

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

    scenario->addEnemy(enemy2);
    // se mueve el primer enemigo
    scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1)[0]->move();

    scenario->addEnemy(enemy1);

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

    scenario->addEnemy(enemy2);
    scenario->addEnemy(enemy1);

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

    scenario->addEnemy(enemy2);
    scenario->addEnemy(enemy1);

    // se obtiene 1 enemigo en el rango especificado
    std::vector<Enemy*> enemies = scenario->getEnemiesInRange(Range(Vector(0, 5), 2), 1);

    CPPUNIT_ASSERT(enemies.empty());
}

void ScenarioTest::towersCanOnlyBePlacedOnFirmGroundTest() {
    YAML::Node config = YAML::LoadFile("config.yaml");
    YAML::Node config_towers = config["towers"];

    // firm_ground hay solo en la posicion (1,5)
    Path path({Vector(0,0), Vector(0,5)});
    Scenario new_scenario(std::move(path), {Vector(1,5)});

    new_scenario.addTower(new FireTower(1, Vector(1,5), config_towers, new_scenario));
    Tower* tower = new FireTower(1, Vector(2,5), config_towers, new_scenario);

    CPPUNIT_ASSERT_THROW(new_scenario.addTower(tower),TowerError);
    CPPUNIT_ASSERT_EQUAL(1, (int)new_scenario.getTowers().size());

    delete tower;
}

void ScenarioTest::cantAddTwoTowersOnTheSamePlaceTest() {
    YAML::Node config = YAML::LoadFile("config.yaml");
    YAML::Node config_towers = config["towers"];

    Path path({Vector(0,0), Vector(0,5)});
    Scenario new_scenario(std::move(path), {Vector(1,5)});

    new_scenario.addTower(new FireTower(1, Vector(1,5), config_towers, new_scenario));

    Tower* tower = new FireTower(1, Vector(2,5), config_towers, new_scenario);

    CPPUNIT_ASSERT_THROW(new_scenario.addTower(tower),TowerError);

    delete tower;
}
