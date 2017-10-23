//
// Created by facundo on 16/10/17.
//

#include "TowerDefenseGameTest.h"
#include "../src/model/Exceptions/EnemyError.h"
#include "../src/model/Exceptions/TowerError.h"
#include "../src/model/Exceptions/MatchError.h"
#include "../src/model/Towers/FireTower.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TowerDefenseGameTest);

void TowerDefenseGameTest::setUp(){
    game = new TowerDefenseGame("map.yaml", "map.yaml");
}

void TowerDefenseGameTest::tearDown() {
    delete game;
}

void TowerDefenseGameTest::addingGreenDemonAddsGreenDemonEnemyWithHisPropertiesTest() {
    game->addEnemy("green_demon");

    const Enemy& green_demon = game->getAllEnemies()[0];

    CPPUNIT_ASSERT_EQUAL(300, green_demon.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(1, (int)green_demon.getSpeed());
    CPPUNIT_ASSERT(!green_demon.canIFlight());
}

void TowerDefenseGameTest::addingAbmonibleAddsAbmonibleEnemyWithHisPropertiesTest() {
    game->addEnemy("abmonible");

    const Enemy& abmonible = game->getAllEnemies()[0];

    CPPUNIT_ASSERT_EQUAL(200, abmonible.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(1, (int)abmonible.getSpeed());
    CPPUNIT_ASSERT(!abmonible.canIFlight());
}

void TowerDefenseGameTest::addingBloodyHawkAddsBloodyHawkEnemyWithHisPropertiesTest() {
    game->addEnemy("bloody_hawk");

    const Enemy& bloody_hawk = game->getAllEnemies()[0];

    CPPUNIT_ASSERT_EQUAL(100, bloody_hawk.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(4, (int)bloody_hawk.getSpeed());
    CPPUNIT_ASSERT(bloody_hawk.canIFlight());
}

void TowerDefenseGameTest::addingSpectrumAddsSpectrumEnemyWithHisPropertiesTest() {
    game->addEnemy("spectrum");

    const Enemy& spectrum = game->getAllEnemies()[0];

    CPPUNIT_ASSERT_EQUAL(100, spectrum.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(6, (int)spectrum.getSpeed());
    CPPUNIT_ASSERT(spectrum.canIFlight());
}

void TowerDefenseGameTest::addingGoatManAddsGoatManEnemyWithHisPropertiesTest() {
    game->addEnemy("goat_man");

    const Enemy& goat_man = game->getAllEnemies()[0];

    CPPUNIT_ASSERT_EQUAL(100, goat_man.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(2, (int)goat_man.getSpeed());
    CPPUNIT_ASSERT(!goat_man.canIFlight());
}

void TowerDefenseGameTest::addingUndeadAddsUndeadEnemyWithHisPropertiesTest() {
    game->addEnemy("undead");

    const Enemy& undead = game->getAllEnemies()[0];

    CPPUNIT_ASSERT_EQUAL(20, undead.getHealthPoints());
    CPPUNIT_ASSERT_EQUAL(10, (int)undead.getSpeed());
    CPPUNIT_ASSERT(!undead.canIFlight());
}

void TowerDefenseGameTest::addingNonExistingEnemyTypeThrowExceptionTest() {
    CPPUNIT_ASSERT_THROW(game->addEnemy("wolo"), EnemyError);
}

void TowerDefenseGameTest::movingEnemiesOverPathTest() {
    game->addEnemy("green_demon");
    game->addEnemy("green_demon");
    game->addEnemy("green_demon");

    const std::vector<Enemy>& enemies = game->getAllEnemies();

    // el path va de (0,0) a (0,5)
    for (int i = 0; i < 15; i++){
        game->moveEnemies();
    }

    Vector final_pos(-1, 2);
    for (const Enemy& enemy: enemies){
        CPPUNIT_ASSERT(final_pos == enemy.getCurrentPosition());
    }
}

void TowerDefenseGameTest::movingEnemiesOverPathWithDistanceBetweenThemTest() {
    const std::vector<Enemy>& enemies = game->getAllEnemies();

    game->addEnemy("green_demon");
    game->moveEnemies();

    game->addEnemy("green_demon");
    game->moveEnemies();

    game->addEnemy("green_demon");

    // el path consiste de 15 movimientos a velocidad = 1
    for (int i = 0; i < 15; i++){
        game->moveEnemies();
    }

    Vector final_pos(-1, 2);
    for (const Enemy& enemy: enemies){
        CPPUNIT_ASSERT(final_pos == enemy.getCurrentPosition());
    }
}

void TowerDefenseGameTest::ifNotAddedPlayerTriesToAddTowerThrowExceptionTest() {
    Player player("alguien", "fire");

    CPPUNIT_ASSERT_THROW(game->addTower(player, "fire", Vector(0,0)), TowerError);
}

void TowerDefenseGameTest::addedPlayerCanAddTowerTest() {
    const Player& added_player = game->addPlayer("alguien", "fire");

    game->addTower(added_player, "fire", Vector(5,5));

    CPPUNIT_ASSERT_NO_THROW(game->addTower(added_player, "fire", Vector(5,5)));
}

void TowerDefenseGameTest::cantAddMoreThanFourPlayersTest() {
    game->addPlayer("jugador1", "fire");
    game->addPlayer("jugador2", "fire");
    game->addPlayer("jugador3", "fire");
    game->addPlayer("jugador4", "fire");

    CPPUNIT_ASSERT_THROW(game->addPlayer("player5", "fire"), MatchError);
}

void TowerDefenseGameTest::whenEnemyIsInRangeOfTowerTheTowerAttacksHimTest() {
    // segun el archivo map.yaml, el path es { (0,0), (0,5), (3,5), (3,2), (-1,2) }
    // y hay terreno firme en (5,5)

    const Player& added_player = game->addPlayer("alguien", "fire");
    game->addTower(added_player, "fire", Vector(5,5));

    game->addEnemy("green_demon");
    const Enemy& enemy = game->getAllEnemies()[0];
    int initial_life = enemy.getHealthPoints();

    // el rango de la torre de fuego es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life > enemy.getHealthPoints());
}

void TowerDefenseGameTest::fireTowerAttacksAllnearbyEnemiesWithLessDamageTest() {
    // segun el archivo map.yaml, el path es { (0,0), (0,5), (3,5), (3,2), (-1,2) }
    // y hay terreno firme en (5,5)

    const Player& added_player = game->addPlayer("alguien", "fire");
    game->addTower(added_player, "fire", Vector(5,5));

    game->addEnemy("green_demon");
    game->addEnemy("green_demon");
    game->addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game->getAllEnemies();

    int initial_life_enemy1 = enemies[0].getHealthPoints();
    int initial_life_enemy2 = enemies[1].getHealthPoints();
    int initial_life_enemy3 = enemies[2].getHealthPoints();

    // el rango de la torre de fuego es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());
    CPPUNIT_ASSERT(initial_life_enemy2 > enemies[1].getHealthPoints());
    CPPUNIT_ASSERT(initial_life_enemy3 > enemies[2].getHealthPoints());

    CPPUNIT_ASSERT(enemies[0].getHealthPoints() < enemies[1].getHealthPoints());
    CPPUNIT_ASSERT(enemies[0].getHealthPoints() < enemies[2].getHealthPoints());
}

void TowerDefenseGameTest::fireTowerDoesNotAttacksEnemiesThatAreNotInRangeTest() {
    const Player& added_player = game->addPlayer("alguien", "fire");
    game->addTower(added_player, "fire", Vector(5,5));

    game->addEnemy("green_demon");
    game->addEnemy("green_demon");
    game->addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game->getAllEnemies();

    int initial_life_enemy1 = enemies[0].getHealthPoints();
    int initial_life_enemy2 = enemies[1].getHealthPoints();
    int initial_life_enemy3 = enemies[2].getHealthPoints();

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 == enemies[0].getHealthPoints());
    CPPUNIT_ASSERT(initial_life_enemy2 == enemies[1].getHealthPoints());
    CPPUNIT_ASSERT(initial_life_enemy3 == enemies[2].getHealthPoints());
}

void TowerDefenseGameTest::fireTowerAttacksOneTimeEveryThreeSecondsTest() {
    const Player& added_player = game->addPlayer("alguien", "fire");
    game->addTower(added_player, "fire", Vector(5,5));

    game->addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game->getAllEnemies();

    int initial_life_enemy1 = enemies[0].getHealthPoints();

    // el rango de la torre de fuego es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());

    initial_life_enemy1 = enemies[0].getHealthPoints();

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 == enemies[0].getHealthPoints());

    sleep(3);

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());
}

void TowerDefenseGameTest::fireTowerDoesNotChangeObjetiveIfItsAliveTest() {
    const Player& added_player = game->addPlayer("alguien", "fire");
    game->addTower(added_player, "fire", Vector(5,5));

    game->addEnemy("green_demon");
    game->moveEnemies();
    game->moveEnemies();
    game->addEnemy("goat_man");

    const Enemy& green_demon = game->getAllEnemies()[0];
    const Enemy& goat_man = game->getAllEnemies()[1];

    int initial_life1 = green_demon.getHealthPoints();
    int initial_life2 = goat_man.getHealthPoints();

    // el rango de la torre de fuego es 3
    for (int i = 0; i < 4; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > goat_man.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == green_demon.getHealthPoints());

    initial_life2 = green_demon.getHealthPoints();

    game->moveEnemies();

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > goat_man.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == green_demon.getHealthPoints());
}

void TowerDefenseGameTest::attackWhenIsInRangeAndStopAttackingWhenIsOutTest() {
    const Player& added_player = game->addPlayer("alguien", "fire");
    game->addTower(added_player, "fire", Vector(5,5));

    game->addEnemy("green_demon");

    const Enemy& enemy = game->getAllEnemies()[0];
    int initial_life = enemy.getHealthPoints();

    // el rango de la torre de fuego es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life > enemy.getHealthPoints());
    initial_life = enemy.getHealthPoints();

    // se sale del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life == enemy.getHealthPoints());

}

void TowerDefenseGameTest::whenEnemyIsInRangeOfWaterTowerItAttacksHimTest() {
    const Player& added_player = game->addPlayer("alguien", "water");
    game->addTower(added_player, "water", Vector(5,5));

    game->addEnemy("green_demon");

    const Enemy& enemy = game->getAllEnemies()[0];
    int initial_life = enemy.getHealthPoints();

    // el rango de la torre de fuego es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life > enemy.getHealthPoints());
}

void TowerDefenseGameTest::waterTowerAttacksOneTimeEveryThreeSecondsTest() {
    const Player& added_player = game->addPlayer("alguien", "water");
    game->addTower(added_player, "water", Vector(5,5));

    game->addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game->getAllEnemies();

    int initial_life_enemy1 = enemies[0].getHealthPoints();

    // el rango de la torre de agua es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());

    initial_life_enemy1 = enemies[0].getHealthPoints();

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 == enemies[0].getHealthPoints());

    sleep(3); // cooldown de la torre

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());
}

void TowerDefenseGameTest::waterTowerDoesNotChangeObjetiveIfItsAliveTest() {
    const Player& added_player = game->addPlayer("alguien", "water");
    game->addTower(added_player, "water", Vector(5,5));

    game->addEnemy("green_demon");
    game->moveEnemies();
    game->moveEnemies();
    game->addEnemy("goat_man");

    const Enemy& enemy = game->getAllEnemies()[0];
    const Enemy& enemy2 = game->getAllEnemies()[1];

    int initial_life1 = enemy.getHealthPoints();
    int initial_life2 = enemy2.getHealthPoints();

    for (int i = 0; i < 4; i++) {
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());

    initial_life2 = enemy2.getHealthPoints();

    game->moveEnemies();

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());
}

void TowerDefenseGameTest::movingEnemiesAndAddingOthersTest() {
    game->addEnemy("green_demon");
    game->moveEnemies();
    game->addEnemy("green_demon");
    game->moveEnemies();

    CPPUNIT_ASSERT_EQUAL(2, (int)game->getAllEnemies()[0].getCurrentPosition().getY());
    CPPUNIT_ASSERT_EQUAL(1, (int)game->getAllEnemies()[1].getCurrentPosition().getY());
}

void TowerDefenseGameTest::waterTowerReduceEnemySpeedTest() {
    const Player& added_player = game->addPlayer("alguien", "water");
    game->addTower(added_player, "water", Vector(5,5));

    game->addEnemy("green_demon");

    float initial_enemy_speed = game->getAllEnemies()[0].getSpeed();

    // el rango de la torre de agua es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++) {
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_enemy_speed > game->getAllEnemies()[0].getSpeed());
}

void TowerDefenseGameTest::waterTowerReduceEnemySpeedDuringTwoSecondsTest() {
    const Player& added_player = game->addPlayer("alguien", "water");
    game->addTower(added_player, "water", Vector(5,5));

    game->addEnemy("green_demon");

    float initial_enemy_speed = game->getAllEnemies()[0].getSpeed();

    // el rango de la torre de agua es 3
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++) {
        game->moveEnemies();
    }

    game->performeAttacks();

    sleep(2);

    CPPUNIT_ASSERT(initial_enemy_speed == game->getAllEnemies()[0].getSpeed());
}

void TowerDefenseGameTest::whenEnemyIsInRangeOfEarthTowerItAttacksHimTest() {
    const Player& added_player = game->addPlayer("alguien", "earth");
    game->addTower(added_player, "earth", Vector(5,5));

    game->addEnemy("green_demon");

    const Enemy& enemy = game->getAllEnemies()[0];
    int initial_life = enemy.getHealthPoints();

    // el rango de la torre de tierra es 2
    // cuando el enemigo se mueve 8 veces, esta en (3,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 8; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life > enemy.getHealthPoints());
}

void TowerDefenseGameTest::earthTowerAttacksOneTimeEveryFiveSecondsTest() {
    const Player& added_player = game->addPlayer("alguien", "earth");
    game->addTower(added_player, "earth", Vector(5,5));

    game->addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game->getAllEnemies();

    int initial_life_enemy1 = enemies[0].getHealthPoints();

    // el rango de la torre de tierra es 2
    // cuando el enemigo se mueve 8 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 8; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());

    initial_life_enemy1 = enemies[0].getHealthPoints();

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 == enemies[0].getHealthPoints());

    sleep(5); // cooldown de la torre

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());
}

void TowerDefenseGameTest::earthTowerDoesNotChangeObjetiveIfItsAliveTest() {
    const Player& added_player = game->addPlayer("alguien", "earth");
    game->addTower(added_player, "earth", Vector(2,4));

    game->addEnemy("green_demon");
    game->moveEnemies();
    game->moveEnemies();
    game->moveEnemies();
    game->addEnemy("goat_man");

    const Enemy& enemy = game->getAllEnemies()[0];
    const Enemy& enemy2 = game->getAllEnemies()[1];

    int initial_life1 = enemy.getHealthPoints();
    int initial_life2 = enemy2.getHealthPoints();

    for (int i = 0; i < 2; i++) {
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());

    initial_life2 = enemy2.getHealthPoints();

    game->moveEnemies();

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());
}

void TowerDefenseGameTest::whenEnemyIsInRangeOfAirTowerItAttacksHimTest() {
    const Player& added_player = game->addPlayer("alguien", "air");
    game->addTower(added_player, "air", Vector(5,5));

    game->addEnemy("green_demon");

    const Enemy& enemy = game->getAllEnemies()[0];
    int initial_life = enemy.getHealthPoints();

    // el rango de la torre de aire es 5
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life > enemy.getHealthPoints());
}

void TowerDefenseGameTest::airTowerAttacksOneTimeEveryFiveSecondsTest() {
    const Player& added_player = game->addPlayer("alguien", "air");
    game->addTower(added_player, "air", Vector(5,5));

    game->addEnemy("green_demon");
    const std::vector<Enemy>& enemies = game->getAllEnemies();

    int initial_life_enemy1 = enemies[0].getHealthPoints();

    // el rango de la torre de aire es 5
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());

    initial_life_enemy1 = enemies[0].getHealthPoints();

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 == enemies[0].getHealthPoints());

    sleep(5); // cooldown de la torre

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life_enemy1 > enemies[0].getHealthPoints());
}

void TowerDefenseGameTest::airTowerDoesNotChangeObjetiveIfItsAliveTest() {
    const Player& added_player = game->addPlayer("alguien", "air");
    game->addTower(added_player, "air", Vector(5,5));

    game->addEnemy("green_demon");
    game->moveEnemies();
    game->addEnemy("goat_man");

    const Enemy& enemy = game->getAllEnemies()[0];
    const Enemy& enemy2 = game->getAllEnemies()[1];

    int initial_life1 = enemy.getHealthPoints();
    int initial_life2 = enemy2.getHealthPoints();

    for (int i = 0; i < 3; i++) {
        game->moveEnemies();
    }

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());

    initial_life2 = enemy2.getHealthPoints();

    game->moveEnemies();

    game->performeAttacks();

    CPPUNIT_ASSERT(initial_life2 > enemy2.getHealthPoints());
    CPPUNIT_ASSERT(initial_life1 == enemy.getHealthPoints());
}

void TowerDefenseGameTest::airTowerMovesBackEnemyWhenHitHimTest() {
    const Player& added_player = game->addPlayer("alguien", "air");
    game->addTower(added_player, "air", Vector(5,5));

    game->addEnemy("green_demon");

    const Enemy& enemy = game->getAllEnemies()[0];

    // el rango de la torre de aire es 5
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    Vector enemy_last_position = enemy.getCurrentPosition();

    game->performeAttacks();

    // cuando le pega el enemigo esta en (3,5) y pasa a (2,5)
    CPPUNIT_ASSERT_EQUAL(1, (int)(enemy_last_position - enemy.getCurrentPosition()).getX());
}

void TowerDefenseGameTest::airTowerHitsFlyingEnemiesHarderTest() {
    const Player& added_player = game->addPlayer("alguien", "air");
    game->addTower(added_player, "air", Vector(5,5));

    game->addEnemy("green_demon");

    const Enemy& green_demon = game->getAllEnemies()[0];

    // el rango de la torre de aire es 5
    // cuando el enemigo se mueve 7 veces, esta en (2,5) y
    // dentro del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    int initial_green_demon_health = green_demon.getHealthPoints();

    game->performeAttacks();

    int dmg_dealed_to_green_demon = initial_green_demon_health
                                             - green_demon.getHealthPoints();

    // se sale de rango el green demon
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->addEnemy("spectrum");

    // se mete en rango de la torre el espectro
    // tiene velocidad 6
    game->moveEnemies();

    const Enemy& spectrum = game->getAllEnemies()[1];

    int initial_spectrum_health = spectrum.getHealthPoints();

    game->performeAttacks();

    int dmg_dealed_to_spectrum = initial_spectrum_health
                                          - spectrum.getHealthPoints();

    CPPUNIT_ASSERT(dmg_dealed_to_spectrum > dmg_dealed_to_green_demon);
}

void TowerDefenseGameTest::whenEnemyIsOutOfRangeFireTowerDoesNotAttackHimTest() {
    const Player& added_player = game->addPlayer("alguien", "fire");
    game->addTower(added_player, "fire", Vector(5,5));

    game->addEnemy("green_demon");

    // se mete en rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    game->performeAttacks();

    game->addEnemy("green_demon");

    // se sale del rango de la torre
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    const Enemy& green_demon = game->getAllEnemies()[0];
    int current_health = green_demon.getHealthPoints();

    game->performeAttacks();

    CPPUNIT_ASSERT(current_health == green_demon.getHealthPoints());
}

void TowerDefenseGameTest::earthTowerCantAttackFlyingUnitsTest() {
    const Player& added_player = game->addPlayer("alguien", "earth");
    game->addTower(added_player, "earth", Vector(2,4));

    game->addEnemy("spectrum");

    // el enemigo se situa en rango de la torre
    game->moveEnemies();

    int initial_life = game->getAllEnemies()[0].getHealthPoints();

    game->performeAttacks();

    CPPUNIT_ASSERT_EQUAL(game->getAllEnemies()[0].getHealthPoints(), initial_life);
}

void TowerDefenseGameTest::addingNotExistingTowerTypeThrowsExceptionTest() {
    const Player& added_player = game->addPlayer("alguien", "earth");

    CPPUNIT_ASSERT_THROW(game->addTower(added_player, "metal", Vector(2,4)), TowerError);
}

void TowerDefenseGameTest::hittingAnEnemyIncreaseFireTowerExperienceByDealedDamagePointsTest() {
    const Player& added_player = game->addPlayer("alguien", "fire");
    const Tower& tower = game->addTower(added_player, "fire", Vector(5,5));

    game->addEnemy("undead");

    // se situa en rango de la torre
    game->moveEnemies();

    game->performeAttacks();

    CPPUNIT_ASSERT(tower.getDamage() == tower.getExperience());
}

void
TowerDefenseGameTest::killingEnemyIncreaseTowerExpByDmgDealedPlusFiftyPercentOfEnemyHealthTest() {
    const Player &added_player = game->addPlayer("alguien", "fire");
    const Tower &tower = game->addTower(added_player, "fire", Vector(5, 5));

    game->addEnemy("undead");

    // se situa en rango de la torre
    game->moveEnemies();

    for (int i = 0; i < 4; i++) {
        // con 4 ataques lo mata
        game->performeAttacks();
    }

    // si la torre lo mata, gana 20 exp + 50% de 20 = 30 exp
    CPPUNIT_ASSERT_EQUAL(30, (int)tower.getExperience());
}

void TowerDefenseGameTest::cantLevelupWaterTowerWithInsuficientExpPointsTest() {
    const Player &added_player = game->addPlayer("alguien", "water");
    const Tower &tower = game->addTower(added_player, "water", Vector(5, 5));

    game->addEnemy("undead");

    // se situa en rango de la torre
    game->moveEnemies();

    for (int i = 0; i < 5; i++) {
        // con 4 ataques lo mata
        game->performeAttacks();
    }

    // cuando lo mata gana 30 de exp y para levelear el rango necesita 200
    CPPUNIT_ASSERT_THROW(game->levelupTower(tower, "range"), TowerError);
}

void TowerDefenseGameTest::whenEarthTowerLevelupHisExperienceIsReducedTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");
    const Tower &tower = game->addTower(added_player, "earth", Vector(2, 4));

    // si mata a 6 suma 180 puntos de exp
    game->addEnemy("undead");
    game->addEnemy("undead");
    game->addEnemy("undead");
    game->addEnemy("undead");
    game->addEnemy("undead");
    game->addEnemy("undead");

    // se situa en rango de la torre
    game->moveEnemies();
    for (int j = 0; j < 6 ; j++){
        // con 1 ataque lo mata
        game->performeAttacks();
    }

    game->levelupTower(tower, "damage");

    CPPUNIT_ASSERT_EQUAL(30, (int)tower.getExperience());
}

void TowerDefenseGameTest::ifCantLevelUpHisExperienceItsNotReducedTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");
    const Tower &tower = game->addTower(added_player, "earth", Vector(2, 4));

    // si mata a 1 suma 30 puntos de exp
    game->addEnemy("undead");

    // se situa en rango de la torre
    game->moveEnemies();
    game->performeAttacks();

    CPPUNIT_ASSERT_THROW(game->levelupTower(tower, "damage"), TowerError);
    CPPUNIT_ASSERT_EQUAL(30, (int)tower.getExperience());
}

void TowerDefenseGameTest::levelingTwoTimesDamageOfEarthTowerIncreaseItByTwentyTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");
    const Tower &tower = game->addTower(added_player, "earth", Vector(2, 4));

    // si mata a 13 suma 390 puntos de exp

    for (int i = 0; i < 13; i++) {
        game->addEnemy("undead");
    }

    // se situa en rango de la torre
    game->moveEnemies();
    for (int j = 0; j < 13 ; j++){
        // con 1 ataque lo mata
        game->performeAttacks();
    }

    game->levelupTower(tower, "damage");
    game->levelupTower(tower, "damage");

    // su daño base es 20. Con dos leveleos es 40
    CPPUNIT_ASSERT_EQUAL(40, (int)tower.getDamage());
    CPPUNIT_ASSERT_EQUAL(15, (int)tower.getExperience());
}

void TowerDefenseGameTest::levelingImpactRangeOfFiretowerIncreasesItByOnesTest() {
    const Player &added_player = game->addPlayer("alguien", "fire");
    const Tower &tower = game->addTower(added_player, "fire", Vector(5, 5));

    game->addEnemy("abmonible");
    game->addEnemy("abmonible");
    game->addEnemy("abmonible");
    game->addEnemy("abmonible");
    game->addEnemy("abmonible");

    // se situa en rango de la torre

    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    // con 34 ataques mueren
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 34; i++){
            game->performeAttacks();
        }
    }

    game->levelupTower(tower, "reach");

    // se agregan dos enemigos con una distancia de 2 entre ellos
    // la torre deberia pegarle al de distancia dos ya que su alcance de impacto
    // paso a ser 2

    game->addEnemy("abmonible");
    game->moveEnemies();
    game->moveEnemies();
    game->addEnemy("abmonible");
    for (int i = 0; i < 7; i++){
        game->moveEnemies();
    }

    int initial_hp = game->getAllEnemies()[6].getHealthPoints();

    game->performeAttacks();

    float dmg_dealed = initial_hp - game->getAllEnemies()[6].getHealthPoints();

    CPPUNIT_ASSERT_EQUAL(3, (int)dmg_dealed);
}

void TowerDefenseGameTest::levelingNotExistingAttributeThrowExceptionTest() {
    const Player &added_player = game->addPlayer("alguien", "air");
    const Tower &tower = game->addTower(added_player, "air", Vector(5, 5));

    CPPUNIT_ASSERT_THROW(game->levelupTower(tower, "wolo"), TowerError);
}

void TowerDefenseGameTest::deadEnemiesAreDestroyedTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");
    const Tower &tower = game->addTower(added_player, "earth", Vector(2, 4));

    game->addEnemy("undead");
    game->moveEnemies();

    game->performeAttacks();
    // ya murio

    game->updateGame();

    CPPUNIT_ASSERT_EQUAL(0, (int)game->getAllEnemies().size());
}

void TowerDefenseGameTest::throwSpellTerraformingCreatesFirmGroundTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");

    game->throwSpell(added_player, "terraforming", Vector(10,10));

    CPPUNIT_ASSERT_NO_THROW(game->addTower(added_player, "earth", Vector(10,10)));
}

void TowerDefenseGameTest::cantThrowTerraformingOverPathTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");

    CPPUNIT_ASSERT_THROW(game->throwSpell(added_player, "terraforming", Vector(0,0)),
                            MatchError);
}

void TowerDefenseGameTest::cantThrowTerraformingOverTowerPositionTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");
    game->addTower(added_player, "earth", Vector(5,5));

    CPPUNIT_ASSERT_THROW(game->throwSpell(added_player, "terraforming", Vector(5,5)),
                         MatchError);
}

void TowerDefenseGameTest::onlyEarthPlayerCanThrowTerraformingTest() {
    const Player &added_player = game->addPlayer("alguien", "fire");

    CPPUNIT_ASSERT_THROW(game->throwSpell(added_player, "terraforming", Vector(10,10)),
                         MatchError);
}

void TowerDefenseGameTest::throwSpellFissureDestroysAllEnemysInPositionTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");

    // comienza en (0,0)
    game->addEnemy("undead");

    game->throwSpell(added_player, "fissure", Vector(0,0));

    game->updateGame();

    CPPUNIT_ASSERT_EQUAL(0, (int)game->getAllEnemies().size());
}

void TowerDefenseGameTest::fissureOnlyLastOneSecondTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");

    game->throwSpell(added_player, "fissure", Vector(0,0));

    sleep(1);

    game->addEnemy("undead");
    game->updateGame();

    CPPUNIT_ASSERT_EQUAL(1, (int)game->getAllEnemies().size());
}

void TowerDefenseGameTest::EnemyPassingThrowFissureDieTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");

    game->throwSpell(added_player, "fissure", Vector(0,1));

    game->addEnemy("green_demon");
    game->moveEnemies();
    game->updateGame();

    CPPUNIT_ASSERT_EQUAL(0, (int)game->getAllEnemies().size());
}

void TowerDefenseGameTest::fissureDoesNotAffectFlyingEnemiesTest() {
    const Player &added_player = game->addPlayer("alguien", "earth");

    // comienza en (0,0)
    game->addEnemy("spectrum");

    game->throwSpell(added_player, "fissure", Vector(0,0));

    game->updateGame();

    CPPUNIT_ASSERT_EQUAL(1, (int)game->getAllEnemies().size());
}

void TowerDefenseGameTest::meteoriteDealsDamageToEnemyHittedTest() {
    const Player &added_player = game->addPlayer("alguien", "fire");

    // comienza en (0,0)
    game->addEnemy("spectrum");
    int enemy_id = game->getAllEnemies()[0].getID();
    int initial_hp = game->getAllEnemies()[0].getHealthPoints();

    game->throwSpell(added_player, "meteorite", enemy_id);

    CPPUNIT_ASSERT(initial_hp > game->getAllEnemies()[0].getHealthPoints());
}

void TowerDefenseGameTest::throwMeteoriteToNotExistingIdThrowsExceptionTest() {
    const Player &added_player = game->addPlayer("alguien", "fire");

    CPPUNIT_ASSERT_THROW(game->throwSpell(added_player, "meteorite", 105), MatchError);
}

void TowerDefenseGameTest::meteoriteHasACooldownTest() {
    const Player &added_player = game->addPlayer("alguien", "fire");

    game->addEnemy("spectrum");
    int enemy_id = game->getAllEnemies()[0].getID();

    game->throwSpell(added_player, "meteorite", enemy_id);

    int hp = game->getAllEnemies()[0].getHealthPoints();

    game->throwSpell(added_player, "meteorite", enemy_id);

    CPPUNIT_ASSERT(hp == game->getAllEnemies()[0].getHealthPoints());
}

void TowerDefenseGameTest::fireWallDealDamageToEnemiesInTheAreaTest() {
    const Player &added_player = game->addPlayer("alguien", "fire");

    // comienzan en (0,0)
    game->addEnemy("spectrum");
    game->addEnemy("spectrum");

    int first_enemy_hp = game->getAllEnemies()[0].getHealthPoints();
    int second_enemy_hp = game->getAllEnemies()[1].getHealthPoints();

    game->throwSpell(added_player, "fire_wall", Vector(0,0));

    game->updateGame();

    CPPUNIT_ASSERT(first_enemy_hp > game->getAllEnemies()[0].getHealthPoints());
    CPPUNIT_ASSERT(second_enemy_hp > game->getAllEnemies()[1].getHealthPoints());
}

void TowerDefenseGameTest::fireWallOnlyLastFiveSecondsTest() {
    const Player &added_player = game->addPlayer("alguien", "fire");

    game->throwSpell(added_player, "fire_wall", Vector(0,0));

    sleep(5);

    game->addEnemy("spectrum");
    int second_enemy_hp = game->getAllEnemies()[0].getHealthPoints();

    game->updateGame();

    CPPUNIT_ASSERT(second_enemy_hp == game->getAllEnemies()[0].getHealthPoints());
}

void TowerDefenseGameTest::freezingStopsTheEnemyHittedTest() {
    const Player &added_player = game->addPlayer("alguien", "water");

    game->addEnemy("spectrum");
    int enemy_id = game->getAllEnemies()[0].getID();

    game->throwSpell(added_player, "freezing", enemy_id);

    CPPUNIT_ASSERT_EQUAL(0, (int)game->getAllEnemies()[0].getSpeed());
}

void TowerDefenseGameTest::freezingOnlyLastFiveSecondsTets() {
    const Player &added_player = game->addPlayer("alguien", "water");

    game->addEnemy("spectrum");
    int enemy_id = game->getAllEnemies()[0].getID();

    Vector initial_position = game->getAllEnemies()[0].getCurrentPosition();
    game->throwSpell(added_player, "freezing", enemy_id);

    game->moveEnemies();

    CPPUNIT_ASSERT(initial_position == game->getAllEnemies()[0].getCurrentPosition());

    sleep(5);

    game->moveEnemies();

    CPPUNIT_ASSERT(game->getAllEnemies()[0].getCurrentPosition() > initial_position);
}

void TowerDefenseGameTest::freezingHasACooldownTest() {
    const Player &added_player = game->addPlayer("alguien", "water");

    game->addEnemy("spectrum");
    int enemy_id = game->getAllEnemies()[0].getID();

    Vector initial_position = game->getAllEnemies()[0].getCurrentPosition();
    game->throwSpell(added_player, "freezing", enemy_id);

    sleep(5);

    game->throwSpell(added_player, "freezing", enemy_id);

    game->moveEnemies();

    CPPUNIT_ASSERT(game->getAllEnemies()[0].getCurrentPosition() > initial_position);
}

void TowerDefenseGameTest::blizzardDealsDamageAndSlowDownEnemiesOnAreaTest() {
    const Player &added_player = game->addPlayer("alguien", "water");

    // esta en la posicion (0,0)
    game->addEnemy("spectrum");
    game->addEnemy("undead");
    const Enemy& spectrum = game->getAllEnemies()[0];
    const Enemy& undead = game->getAllEnemies()[1];

    float spectrum_initial_speed = spectrum.getSpeed();
    int spectrum_initial_hp = spectrum.getHealthPoints();
    float undead_initial_speed = undead.getSpeed();
    int undead_initial_hp = undead.getHealthPoints();

    game->throwSpell(added_player, "blizzard", Vector(0,0));
    game->updateGame();

    float spectrum_reduced_speed = spectrum.getSpeed();
    int spectrum_reduced_hp = spectrum.getHealthPoints();
    float undead_reduced_speed = undead.getSpeed();
    int undead_reduced_hp = undead.getHealthPoints();

    CPPUNIT_ASSERT(spectrum_initial_speed > spectrum_reduced_speed);
    CPPUNIT_ASSERT(spectrum_initial_hp > spectrum_reduced_hp);
    CPPUNIT_ASSERT(undead_initial_speed > undead_reduced_speed);
    CPPUNIT_ASSERT(undead_initial_hp > undead_reduced_hp);
}

void TowerDefenseGameTest::blizzardHasACooldownTest() {
    const Player &added_player = game->addPlayer("alguien", "water");

    // esta en la posicion (0,0)
    game->addEnemy("spectrum");
    const Enemy& spectrum = game->getAllEnemies()[0];

    game->throwSpell(added_player, "blizzard", Vector(0,0));
    game->updateGame();

    int actual_hp = spectrum.getHealthPoints();

    sleep(5);
    game->throwSpell(added_player, "blizzard", Vector(0,0));
    game->updateGame();

    int reduced_hp = spectrum.getHealthPoints();

    CPPUNIT_ASSERT(actual_hp == reduced_hp);
}
