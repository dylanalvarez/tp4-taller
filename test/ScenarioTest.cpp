//
// Created by facundo on 15/10/17.
//

#include "ScenarioTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ScenarioTest);

ScenarioTest::ScenarioTest() {
    Path path({Vector(0,0), Vector(0,5)});
    YAML::Node config = YAML::LoadFile("map.yaml");
    scenario = new Scenario(std::move(path), config);
}

ScenarioTest::~ScenarioTest() {
    delete scenario;
}

void ScenarioTest::getEnemyInRangeTest() {
    int enemy_id = 1;
    scenario->addEnemy(enemy_id,"green_demon");

    // se obtiene 1 enemigo en el rango especificado
    std::vector<Enemy*> enemies = scenario->getEnemiesInRange(Range(Vector(0, 0), 2), 1);

    CPPUNIT_ASSERT_EQUAL(1, (int)enemies.size());
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

    CPPUNIT_ASSERT_EQUAL(1, (int)enemies.size());
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

    CPPUNIT_ASSERT_EQUAL(1, (int)enemies.size());
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

void ScenarioTest::addingGreenDemonAddsGreenDemonEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "green_demon");

    const std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& green_demon = enemies[0];

    CPPUNIT_ASSERT_EQUAL(300, (int)green_demon.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(1, (int)green_demon.getSpeed());
    CPPUNIT_ASSERT(!green_demon.canIFlight());
}

void ScenarioTest::addingAbmonibleAddsAbmonibleEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "abmonible");

    const std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& abmonible = enemies[0];

    CPPUNIT_ASSERT_EQUAL(200, (int)abmonible.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(1, (int)abmonible.getSpeed());
    CPPUNIT_ASSERT(!abmonible.canIFlight());
}

void ScenarioTest::addingBloodyHawkAddsBloodyHawkEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "bloody_hawk");

    const std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& bloody_hawk = enemies[0];

    CPPUNIT_ASSERT_EQUAL(100, (int)bloody_hawk.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(4, (int)bloody_hawk.getSpeed());
    CPPUNIT_ASSERT(bloody_hawk.canIFlight());
}

void ScenarioTest::addingSpectrumAddsSpectrumEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "spectrum");

    const std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& spectrum = enemies[0];

    CPPUNIT_ASSERT_EQUAL(100, (int)spectrum.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(6, (int)spectrum.getSpeed());
    CPPUNIT_ASSERT(spectrum.canIFlight());
}

void ScenarioTest::addingGoatManAddsGoatManEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "goat_man");

    const std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& goat_man = enemies[0];

    CPPUNIT_ASSERT_EQUAL(100, (int)goat_man.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(2, (int)goat_man.getSpeed());
    CPPUNIT_ASSERT(!goat_man.canIFlight());
}

void ScenarioTest::addingUndeadAddsUndeadEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "undead");

    const std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& undead = enemies[0];

    CPPUNIT_ASSERT_EQUAL(20, (int)undead.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(10, (int)undead.getSpeed());
    CPPUNIT_ASSERT(!undead.canIFlight());
}

void ScenarioTest::addingNonExistingEnemyTypeDoesNothingTest() {
    scenario->addEnemy(1, "wolo");
}