//
// Created by facundo on 16/10/17.
//

#include "TowerDefenseGame.h"
#include "Exceptions/EnemyError.h"
#include "Exceptions/TowerError.h"
#include "Exceptions/MatchError.h"
#include "Factory/FireTowerFactory.h"
#include "Factory/WaterTowerFactory.h"
#include "Factory/EarthTowerFactory.h"
#include "Factory/AirTowerFactory.h"

TowerDefenseGame::TowerDefenseGame(const std::string &config_file,
                                   const std::string &scenario_file) {
    YAML::Node config = YAML::LoadFile(config_file);

    loadEnemyProperties(config);
    loadTowerProperties(config);
    // cargar propiedades de las torres
    // cargar propiedades del escenario

    tower_id = 1;
    enemy_id = 1;
    Path path({Vector(0,0), Vector(0,5), Vector(3,5),
               Vector(3,2), Vector(-1, 2)});

    std::vector<Vector> firm_ground_locations = {Vector(5,5), Vector(2,4)};

    scenario = new Scenario(std::move(path), std::move(firm_ground_locations));
}

TowerDefenseGame::~TowerDefenseGame(){
    delete scenario;

    for (auto& tower_factory : towers_factory) {
        delete tower_factory.second;
    }
}

void TowerDefenseGame::addEnemy(const std::string &enemy_type) {
    try{
        EnemyProperties properties = enemies_properties.at(enemy_type);
        Enemy enemy(enemy_id++, scenario->getPath(), properties.hp, properties.speed,
                             properties.does_it_fly);
        scenario->addEnemy(enemy);
    } catch (std::exception& e) {
        throw EnemyError("Error al agregar enemigo -> El tipo: " + enemy_type
                         + " no es un tipo valido");
    }
}

void TowerDefenseGame::loadEnemyProperties(YAML::Node& config) {
    typedef std::pair<std::string, EnemyProperties> pair;

    // green_demon
    EnemyProperties properties(300, 1, false);
    pair green_demon("green_demon", properties);
    // abmonible
    properties.hp = 200;
    pair abmonible("abmonible", properties);
    // goat_man
    properties.hp = 100;
    properties.speed = 2;
    pair goat_man("goat_man", properties);
    // undead
    properties.hp = 20;
    properties.speed = 10;
    pair undead("undead", properties);
    // bloody_hawk
    properties.hp = 100;
    properties.speed = 4;
    properties.does_it_fly = true;
    pair bloody_hawk("bloody_hawk", properties);
    // spectrum
    properties.speed = 6;
    pair spectrum("spectrum", properties);

    enemies_properties.insert(abmonible);
    enemies_properties.insert(green_demon);
    enemies_properties.insert(bloody_hawk);
    enemies_properties.insert(spectrum);
    enemies_properties.insert(goat_man);
    enemies_properties.insert(undead);
}

const std::vector<Enemy> &TowerDefenseGame::getAllEnemies() const {
    return scenario->getAllEnemies();
}

void TowerDefenseGame::moveEnemies() {
    for (Enemy& enemy : scenario->getAllEnemies()){
        enemy.move();
    }
}

bool TowerDefenseGame::doesPlayerExist(const Player &player) {
    for (Player& p : players) {
        if (&p == &player){
            return true;
        }
    }
    return false;
}

const Tower& TowerDefenseGame::addTower(const Player &player, const std::string &type,
                                const Vector &position) {
    if (!doesPlayerExist(player)) {
        throw TowerError("Error al añadir la torre de tipo " + type +
                         ", el jugador " + player.getName() +
                         "no pertence a la partida");
    }
    Tower* tower;
    try {
        tower = towers_factory.at(type)->create(tower_id++, position,
                                                       tower_properties, *scenario);
        scenario->addTower(tower);
        return *tower;
    } catch (std::exception& e) {
        throw TowerError("Error: el tipo de torre " + type + " no es un tipo valido");
    }
}

const Player& TowerDefenseGame::addPlayer(const std::string &name) {
    if (players.size() == 4) { throw MatchError("Error al añadir jugador: " +
                                                       name + ": partida llena");}
    players.emplace_back(name);
    return players.back();
}

void TowerDefenseGame::performeAttacks() {
    for (auto& tower: scenario->getTowers()){
        tower->attack();
    }
}

void TowerDefenseGame::loadTowerProperties(YAML::Node& properties) {
    tower_properties = properties;
    towers_factory.emplace("fire", new FireTowerFactory());
    towers_factory.emplace("water", new WaterTowerFactory());
    towers_factory.emplace("earth", new EarthTowerFactory());
    towers_factory.emplace("air", new AirTowerFactory());
}

void TowerDefenseGame::levelupTower(const Tower& tower, const std::string& type) {
    scenario->levelupTower(tower, type);
}
