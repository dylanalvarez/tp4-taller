//
// Created by facundo on 15/10/17.
//

#include "ScenarioTest.h"
#include "../src/model/Exceptions/EnemyError.h"

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

    std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& green_demon = enemies[0];

    CPPUNIT_ASSERT_EQUAL(300, (int)green_demon.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(1, (int)green_demon.getSpeed());
    CPPUNIT_ASSERT(!green_demon.canIFlight());
}

void ScenarioTest::addingAbmonibleAddsAbmonibleEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "abmonible");

    std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& abmonible = enemies[0];

    CPPUNIT_ASSERT_EQUAL(200, (int)abmonible.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(1, (int)abmonible.getSpeed());
    CPPUNIT_ASSERT(!abmonible.canIFlight());
}

void ScenarioTest::addingBloodyHawkAddsBloodyHawkEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "bloody_hawk");

    std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& bloody_hawk = enemies[0];

    CPPUNIT_ASSERT_EQUAL(100, (int)bloody_hawk.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(4, (int)bloody_hawk.getSpeed());
    CPPUNIT_ASSERT(bloody_hawk.canIFlight());
}

void ScenarioTest::addingSpectrumAddsSpectrumEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "spectrum");

    std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& spectrum = enemies[0];

    CPPUNIT_ASSERT_EQUAL(100, (int)spectrum.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(6, (int)spectrum.getSpeed());
    CPPUNIT_ASSERT(spectrum.canIFlight());
}

void ScenarioTest::addingGoatManAddsGoatManEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "goat_man");

    std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& goat_man = enemies[0];

    CPPUNIT_ASSERT_EQUAL(100, (int)goat_man.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(2, (int)goat_man.getSpeed());
    CPPUNIT_ASSERT(!goat_man.canIFlight());
}

void ScenarioTest::addingUndeadAddsUndeadEnemyWithHisPropertiesTest() {
    scenario->addEnemy(1, "undead");

    std::vector<Enemy>& enemies = scenario->getAllEnemies();

    const Enemy& undead = enemies[0];

    CPPUNIT_ASSERT_EQUAL(20, (int)undead.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(10, (int)undead.getSpeed());
    CPPUNIT_ASSERT(!undead.canIFlight());
}

void ScenarioTest::addingNonExistingEnemyTypeThrowExceptionTest() {
    CPPUNIT_ASSERT_THROW(scenario->addEnemy(1, "wolo"), EnemyError);
}

void ScenarioTest::addTwoEnemiesWithSameIdThrowExceptionTest() {
    scenario->addEnemy(1, "undead");

    CPPUNIT_ASSERT_THROW(scenario->addEnemy(1, "goat_man"), EnemyError);
}

void ScenarioTest::movingEnemiesOverPathTest() {
    scenario->addEnemy(1, "green_demon");
    scenario->addEnemy(2, "green_demon");
    scenario->addEnemy(3, "green_demon");

    std::vector<Enemy>& enemies = scenario->getAllEnemies();

    // el path va de (0,0) a (0,5)
    for (int i = 0; i < 6; i++){
        for (Enemy& enemy : enemies){
            enemy.move();
        }
    }

    Vector final_pos(0,5);
    for (Enemy& enemy: enemies){
        CPPUNIT_ASSERT(final_pos == enemy.getCurrentPosition());
    }
}

void ScenarioTest::movingEnemiesOverPathWithDistanceBetweenThemTest() {
    std::vector<Enemy>& enemies = scenario->getAllEnemies();

    scenario->addEnemy(1, "green_demon");
    enemies[0].move();

    scenario->addEnemy(2, "green_demon");
    enemies[0].move();
    enemies[1].move();

    scenario->addEnemy(3, "green_demon");

    // el path va de (0,0) a (0,5)
    for (int i = 0; i < 6; i++){
        for (Enemy& enemy : enemies){
            enemy.move();
        }
    }

    Vector final_pos(0,5);
    for (Enemy& enemy: enemies){
        CPPUNIT_ASSERT(final_pos == enemy.getCurrentPosition());
    }
}

void ScenarioTest::movingEnemiesOverCurvedPathTest() {
    Path path({Vector(0,0), Vector(0,5), Vector(3,5), Vector(3,2), Vector(-1,2)});

    YAML::Node config = YAML::LoadFile("map.yaml");

    Scenario scenario1(std::move(path), config);

    std::vector<Enemy>& enemies = scenario1.getAllEnemies();

    scenario1.addEnemy(1, "green_demon");
    scenario1.addEnemy(2, "green_demon");

    for (int i = 0; i < 15; i++){
        enemies[0].move();
        enemies[1].move();
    }

    Vector final_pos(-1,2);
    for (Enemy& enemy: enemies){
        CPPUNIT_ASSERT(final_pos == enemy.getCurrentPosition());
    }
}