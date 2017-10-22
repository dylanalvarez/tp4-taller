//
// Created by facundo on 16/10/17.
//

#include "TowerDefenseGameTest.h"
#include "../src/model/Exceptions/EnemyError.h"
#include "../src/model/Exceptions/TowerError.h"
#include "../src/model/Exceptions/MatchError.h"

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

void TowerDefenseGameTest::ifNotAddedPlayerTriesToAddTowerThrowExceptionTest() {
    Player player("alguien");

    CPPUNIT_ASSERT_THROW(game.addTower(player, "fire", Vector(0,0)), TowerError);
}

void TowerDefenseGameTest::addedPlayerCanAddTowerTest() {
    const Player& added_player = game.addPlayer("alguien");

    game.addTower(added_player, "fire", Vector(5,5));

    CPPUNIT_ASSERT_NO_THROW(game.addTower(added_player, "fire", Vector(5,5)));
}

void TowerDefenseGameTest::cantAddMoreThanFourPlayersTest() {
    game.addPlayer("jugador1");
    game.addPlayer("jugador2");
    game.addPlayer("jugador3");
    game.addPlayer("jugador4");

    CPPUNIT_ASSERT_THROW(game.addPlayer("player5"), MatchError);
}

void TowerDefenseGameTest::whenEnemyIsInRangeOfTowerTheTowerAttacksHimTest() {
    // segun el archivo map.yaml, el path es { (0,0), (0,5), (3,5), (3,2), (-1,2) }
    // y hay terreno firme en (5,5)

    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "fire", Vector(5,5));

    game.addEnemy("green_demon");
    const Enemy& enemy = game.getAllEnemies()[0];
    unsigned int initial_life = enemy.getHealthPoints();

    // el rango de la torre de fuego es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life > enemy.getHealthPoints());
}

void TowerDefenseGameTest::fireTowerAttacksAllnearbyEnemiesWithLessDamageTest() {
    // segun el archivo map.yaml, el path es { (0,0), (0,5), (3,5), (3,2), (-1,2) }
    // y hay terreno firme en (5,5)

    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "fire", Vector(5,5));

    game.addEnemy("green_demon");
    game.addEnemy("green_demon");
    game.addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game.getAllEnemies();

    unsigned int initial_life_enemy1 = enemies[0].getHealthPoints();
    unsigned int initial_life_enemy2 = enemies[1].getHealthPoints();
    unsigned int initial_life_enemy3 = enemies[2].getHealthPoints();

    // el rango de la torre de fuego es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());
    CPPUNIT_ASSERT(initial_life_enemy2 > enemies[1].getHealthPoints());
    CPPUNIT_ASSERT(initial_life_enemy3 > enemies[2].getHealthPoints());

    CPPUNIT_ASSERT(enemies[0].getHealthPoints() < enemies[1].getHealthPoints());
    CPPUNIT_ASSERT(enemies[0].getHealthPoints() < enemies[2].getHealthPoints());
}

void TowerDefenseGameTest::fireTowerDoesNotAttacksEnemiesThatAreNotInRangeTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "fire", Vector(5,5));

    game.addEnemy("green_demon");
    game.addEnemy("green_demon");
    game.addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game.getAllEnemies();

    unsigned int initial_life_enemy1 = enemies[0].getHealthPoints();
    unsigned int initial_life_enemy2 = enemies[1].getHealthPoints();
    unsigned int initial_life_enemy3 = enemies[2].getHealthPoints();

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 = enemies[0].getHealthPoints());
    CPPUNIT_ASSERT(initial_life_enemy2 = enemies[1].getHealthPoints());
    CPPUNIT_ASSERT(initial_life_enemy3 = enemies[2].getHealthPoints());
}

void TowerDefenseGameTest::fireTowerAttacksOneTimeEveryThreeSecondsTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "fire", Vector(5,5));

    game.addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game.getAllEnemies();

    unsigned int initial_life_enemy1 = enemies[0].getHealthPoints();

    // el rango de la torre de fuego es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());

    initial_life_enemy1 = enemies[0].getHealthPoints();

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 == enemies[0].getHealthPoints());

    sleep(3);

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());
}

void TowerDefenseGameTest::fireTowerDoesNotChangeObjetiveIfItsAliveTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "fire", Vector(5,5));

    game.addEnemy("green_demon");
    game.moveEnemies();
    game.moveEnemies();
    game.addEnemy("goat_man");

    const Enemy& green_demon = game.getAllEnemies()[0];
    const Enemy& goat_man = game.getAllEnemies()[1];

    unsigned int initial_life1 = green_demon.getHealthPoints();
    unsigned int initial_life2 = goat_man.getHealthPoints();

    // el rango de la torre de fuego es 3
    for (int i = 0; i < 4; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > goat_man.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == green_demon.getHealthPoints());

    initial_life2 = green_demon.getHealthPoints();

    game.moveEnemies();

    sleep(3);

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > goat_man.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == green_demon.getHealthPoints());
}

void TowerDefenseGameTest::attackWhenIsInRangeAndStopAttackingWhenIsOutTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "fire", Vector(5,5));

    game.addEnemy("green_demon");

    const Enemy& enemy = game.getAllEnemies()[0];
    unsigned int initial_life = enemy.getHealthPoints();

    // el rango de la torre de fuego es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.performeAttacks();
    sleep(3); // cooldown de la torre de fuego

    CPPUNIT_ASSERT(initial_life > enemy.getHealthPoints());
    initial_life = enemy.getHealthPoints();

    // se sale del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life == enemy.getHealthPoints());

}

void TowerDefenseGameTest::whenEnemyIsInRangeOfWaterTowerItAttacksHimTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "water", Vector(5,5));

    game.addEnemy("green_demon");

    const Enemy& enemy = game.getAllEnemies()[0];
    unsigned int initial_life = enemy.getHealthPoints();

    // el rango de la torre de fuego es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life > enemy.getHealthPoints());
}

void TowerDefenseGameTest::waterTowerAttacksOneTimeEveryThreeSecondsTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "water", Vector(5,5));

    game.addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game.getAllEnemies();

    unsigned int initial_life_enemy1 = enemies[0].getHealthPoints();

    // el rango de la torre de agua es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());

    initial_life_enemy1 = enemies[0].getHealthPoints();

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 == enemies[0].getHealthPoints());

    sleep(3); // cooldown de la torre

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());
}

void TowerDefenseGameTest::waterTowerDoesNotChangeObjetiveIfItsAliveTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "water", Vector(5,5));

    game.addEnemy("green_demon");
    game.moveEnemies();
    game.moveEnemies();
    game.addEnemy("goat_man");

    const Enemy& enemy = game.getAllEnemies()[0];
    const Enemy& enemy2 = game.getAllEnemies()[1];

    unsigned int initial_life1 = enemy.getHealthPoints();
    unsigned int initial_life2 = enemy2.getHealthPoints();

    for (int i = 0; i < 4; i++) {
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());

    initial_life2 = enemy2.getHealthPoints();

    game.moveEnemies();

    sleep(3); // cooldown de la torre

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());
}

void TowerDefenseGameTest::movingEnemiesAndAddingOthersTest() {
    game.addEnemy("green_demon");
    game.moveEnemies();
    game.addEnemy("green_demon");
    game.moveEnemies();

    CPPUNIT_ASSERT_EQUAL(2, (int)game.getAllEnemies()[0].getCurrentPosition().getY());
    CPPUNIT_ASSERT_EQUAL(1, (int)game.getAllEnemies()[1].getCurrentPosition().getY());
}

void TowerDefenseGameTest::waterTowerReduceEnemySpeedTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "water", Vector(5,5));

    game.addEnemy("green_demon");

    float initial_enemy_speed = game.getAllEnemies()[0].getSpeed();

    // el rango de la torre de agua es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++) {
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_enemy_speed > game.getAllEnemies()[0].getSpeed());
}

void TowerDefenseGameTest::waterTowerReduceEnemySpeedDuringTwoSecondsTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "water", Vector(5,5));

    game.addEnemy("green_demon");

    float initial_enemy_speed = game.getAllEnemies()[0].getSpeed();

    // el rango de la torre de agua es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++) {
        game.moveEnemies();
    }

    game.performeAttacks();

    sleep(2); // speed reduction's cooldown

    CPPUNIT_ASSERT(initial_enemy_speed == game.getAllEnemies()[0].getSpeed());
}

void TowerDefenseGameTest::whenEnemyIsInRangeOfEarthTowerItAttacksHimTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "earth", Vector(5,5));

    game.addEnemy("green_demon");

    const Enemy& enemy = game.getAllEnemies()[0];
    unsigned int initial_life = enemy.getHealthPoints();

    // el rango de la torre de tierra es 2
    // cuando el enemigo se mueve 8 veces, esta en (3,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 8; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life > enemy.getHealthPoints());
}

void TowerDefenseGameTest::earthTowerAttacksOneTimeEveryFiveSecondsTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "earth", Vector(5,5));

    game.addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game.getAllEnemies();

    unsigned int initial_life_enemy1 = enemies[0].getHealthPoints();

    // el rango de la torre de tierra es 2
    // cuando el enemigo se mueve 8 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 8; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());

    initial_life_enemy1 = enemies[0].getHealthPoints();

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 == enemies[0].getHealthPoints());

    sleep(5); // cooldown de la torre

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());
}

void TowerDefenseGameTest::earthTowerDoesNotChangeObjetiveIfItsAliveTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "earth", Vector(2,4));

    game.addEnemy("green_demon");
    game.moveEnemies();
    game.moveEnemies();
    game.moveEnemies();
    game.addEnemy("goat_man");

    const Enemy& enemy = game.getAllEnemies()[0];
    const Enemy& enemy2 = game.getAllEnemies()[1];

    unsigned int initial_life1 = enemy.getHealthPoints();
    unsigned int initial_life2 = enemy2.getHealthPoints();

    for (int i = 0; i < 2; i++) {
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());

    initial_life2 = enemy2.getHealthPoints();

    game.moveEnemies();

    sleep(5); // cooldown de la torre

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());
}

void TowerDefenseGameTest::whenEnemyIsInRangeOfAirTowerItAttacksHimTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "air", Vector(5,5));

    game.addEnemy("green_demon");

    const Enemy& enemy = game.getAllEnemies()[0];
    unsigned int initial_life = enemy.getHealthPoints();

    // el rango de la torre de aire es 5
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life > enemy.getHealthPoints());
}

void TowerDefenseGameTest::airTowerAttacksOneTimeEveryFiveSecondsTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "air", Vector(5,5));

    game.addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game.getAllEnemies();

    unsigned int initial_life_enemy1 = enemies[0].getHealthPoints();

    // el rango de la torre de aire es 5
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());

    initial_life_enemy1 = enemies[0].getHealthPoints();

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 == enemies[0].getHealthPoints());

    sleep(5); // cooldown de la torre

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());
}

void TowerDefenseGameTest::airTowerDoesNotChangeObjetiveIfItsAliveTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "air", Vector(5,5));

    game.addEnemy("green_demon");
    game.moveEnemies();
    game.addEnemy("goat_man");

    const Enemy& enemy = game.getAllEnemies()[0];
    const Enemy& enemy2 = game.getAllEnemies()[1];

    unsigned int initial_life1 = enemy.getHealthPoints();
    unsigned int initial_life2 = enemy2.getHealthPoints();

    for (int i = 0; i < 3; i++) {
        game.moveEnemies();
    }

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());

    initial_life2 = enemy2.getHealthPoints();

    game.moveEnemies();

    sleep(5); // cooldown de la torre

    game.performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());
}

void TowerDefenseGameTest::airTowerMovesBackEnemyWhenHitHimTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "air", Vector(5,5));

    game.addEnemy("green_demon");

    const Enemy& enemy = game.getAllEnemies()[0];

    // el rango de la torre de aire es 5
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    Vector enemy_last_position = enemy.getCurrentPosition();

    game.performeAttacks();

    // cuando le pega el enemigo esta en (3,5) y pasa a (2,5)
    CPPUNIT_ASSERT_EQUAL(1, (int)(enemy_last_position - enemy.getCurrentPosition()).getX());
}

void TowerDefenseGameTest::airTowerHitsFlyingEnemiesHarderTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "air", Vector(5,5));

    game.addEnemy("green_demon");

    const Enemy& green_demon = game.getAllEnemies()[0];

    // el rango de la torre de aire es 5
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    unsigned int initial_green_demon_health = green_demon.getHealthPoints();

    game.performeAttacks();
    sleep(5); // air tower cooldown

    unsigned int dmg_dealed_to_green_demon = initial_green_demon_health
                                             - green_demon.getHealthPoints();

    // se sale de rango el green demon
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.addEnemy("spectrum");

    // se mete en rango de la torre el espectro
    // tiene velocidad 6
    game.moveEnemies();

    const Enemy& spectrum = game.getAllEnemies()[1];

    unsigned int initial_spectrum_health = spectrum.getHealthPoints();

    game.performeAttacks();

    unsigned int dmg_dealed_to_spectrum = initial_spectrum_health
                                          - spectrum.getHealthPoints();

    CPPUNIT_ASSERT(dmg_dealed_to_spectrum > dmg_dealed_to_green_demon);
}

void TowerDefenseGameTest::whenEnemyIsOutOfRangeFireTowerDoesNotAttackHimTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "fire", Vector(5,5));

    game.addEnemy("green_demon");

    // se mete en rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    game.performeAttacks();
    sleep(3); // fire tower cooldown

    game.addEnemy("green_demon");

    // se sale del rango de la torre
    for (int i = 0; i < 7; i++){
        game.moveEnemies();
    }

    const Enemy& green_demon = game.getAllEnemies()[0];
    unsigned int current_health = green_demon.getHealthPoints();

    game.performeAttacks();

    CPPUNIT_ASSERT(current_health == green_demon.getHealthPoints());
}

void TowerDefenseGameTest::earthTowerCantAttackFlyingUnitsTest() {
    const Player& added_player = game.addPlayer("alguien");
    game.addTower(added_player, "earth", Vector(2,4));

    game.addEnemy("spectrum");

    // el enemigo se situa en rango de la torre
    game.moveEnemies();

    unsigned int initial_life = game.getAllEnemies()[0].getHealthPoints();

    game.performeAttacks();

    CPPUNIT_ASSERT_EQUAL(game.getAllEnemies()[0].getHealthPoints(), initial_life);
}
