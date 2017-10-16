//
// Created by facundo on 16/10/17.
//

#include "TowerDefenseGameTest.h"
#include "../src/model/Exceptions/EnemyError.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TowerDefenseGameTest);

TowerDefenseGameTest::TowerDefenseGameTest() : game("map.yaml", "map.yaml") {}


void TowerDefenseGameTest::addingGreenDemonAddsGreenDemonEnemyWithHisPropertiesTest() {
    game.addEnemy("green_demon");

    const std::vector<Enemy>& enemies = game.getAllEnemies();

    const Enemy& green_demon = enemies[0];

    CPPUNIT_ASSERT_EQUAL(300, (int)green_demon.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(1, (int)green_demon.getSpeed());
    CPPUNIT_ASSERT(!green_demon.canIFlight());
}

void TowerDefenseGameTest::addingAbmonibleAddsAbmonibleEnemyWithHisPropertiesTest() {
    game.addEnemy("abmonible");

    const std::vector<Enemy>& enemies = game.getAllEnemies();

    const Enemy& abmonible = enemies[0];

    CPPUNIT_ASSERT_EQUAL(200, (int)abmonible.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(1, (int)abmonible.getSpeed());
    CPPUNIT_ASSERT(!abmonible.canIFlight());
}

void TowerDefenseGameTest::addingBloodyHawkAddsBloodyHawkEnemyWithHisPropertiesTest() {
    game.addEnemy("bloody_hawk");

    const std::vector<Enemy>& enemies = game.getAllEnemies();

    const Enemy& bloody_hawk = enemies[0];

    CPPUNIT_ASSERT_EQUAL(100, (int)bloody_hawk.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(4, (int)bloody_hawk.getSpeed());
    CPPUNIT_ASSERT(bloody_hawk.canIFlight());
}

void TowerDefenseGameTest::addingSpectrumAddsSpectrumEnemyWithHisPropertiesTest() {
    game.addEnemy("spectrum");

    const std::vector<Enemy>& enemies = game.getAllEnemies();

    const Enemy& spectrum = enemies[0];

    CPPUNIT_ASSERT_EQUAL(100, (int)spectrum.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(6, (int)spectrum.getSpeed());
    CPPUNIT_ASSERT(spectrum.canIFlight());
}

void TowerDefenseGameTest::addingGoatManAddsGoatManEnemyWithHisPropertiesTest() {
    game.addEnemy("goat_man");

    const std::vector<Enemy>& enemies = game.getAllEnemies();

    const Enemy& goat_man = enemies[0];

    CPPUNIT_ASSERT_EQUAL(100, (int)goat_man.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(2, (int)goat_man.getSpeed());
    CPPUNIT_ASSERT(!goat_man.canIFlight());
}

void TowerDefenseGameTest::addingUndeadAddsUndeadEnemyWithHisPropertiesTest() {
    game.addEnemy("undead");

    const std::vector<Enemy>& enemies = game.getAllEnemies();

    const Enemy& undead = enemies[0];

    CPPUNIT_ASSERT_EQUAL(20, (int)undead.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(10, (int)undead.getSpeed());
    CPPUNIT_ASSERT(!undead.canIFlight());
}

void TowerDefenseGameTest::addingNonExistingEnemyTypeThrowExceptionTest() {
    CPPUNIT_ASSERT_THROW(game.addEnemy("wolo"), EnemyError);
}

void TowerDefenseGameTest::movingEnemiesOverPathTest() {
    game.addEnemy("green_demon");
    game.addEnemy("green_demon");
    game.addEnemy("green_demon");

    const std::vector<Enemy>& enemies = game.getAllEnemies();

    // el path va de (0,0) a (0,5)
    for (int i = 0; i < 15; i++){
        game.moveEnemies();
    }

    Vector final_pos(-1, 2);
    for (const Enemy& enemy: enemies){
        CPPUNIT_ASSERT(final_pos == enemy.getCurrentPosition());
    }
}

void TowerDefenseGameTest::movingEnemiesOverPathWithDistanceBetweenThemTest() {
    const std::vector<Enemy>& enemies = game.getAllEnemies();

    game.addEnemy("green_demon");
    game.moveEnemies();

    game.addEnemy("green_demon");
    game.moveEnemies();

    game.addEnemy("green_demon");

    // el path consiste de 15 movimientos a velocidad = 1
    for (int i = 0; i < 15; i++){
        game.moveEnemies();
    }

    Vector final_pos(-1, 2);
    for (const Enemy& enemy: enemies){
        CPPUNIT_ASSERT(final_pos == enemy.getCurrentPosition());
    }
}

