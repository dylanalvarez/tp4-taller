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
#include "Spells/Terraforming.h"
#include "Spells/Fissure.h"
#include "Spells/Meteorite.h"
#include "Spells/FireWall.h"
#include "Spells/Freezing.h"
#include "Spells/Blizzard.h"
#include "Spells/Tornato.h"
#include "Spells/Ray.h"

TowerDefenseGame::TowerDefenseGame(const std::string &config_file,
                                   const std::string &scenario_file) {
    YAML::Node config = YAML::LoadFile(config_file);
    YAML::Node map = YAML::LoadFile(scenario_file);
    YAML::Node towers_file = config["towers"];

    loadEnemyProperties(config);
    loadTowerProperties(towers_file);
    loadScenarioProperties(map);

    tower_id = 1;
    enemy_id = 1;

    spells.emplace("terraforming", new Terraforming(*scenario, 20));
    spells.emplace("fissure", new Fissure(*scenario, 40, 1));
    spells.emplace("meteorite", new Meteorite(*scenario, 20, 2, 30, 10));
    spells.emplace("fire_wall", new FireWall(*scenario, 10, 10, 5));
    spells.emplace("freezing", new Freezing(*scenario, 15, 5));
    spells.emplace("blizzard", new Blizzard(*scenario, 20, 5, 5, 25, 2));
    spells.emplace("tornato", new Tornato(*scenario, 20, 1, 50, 10));
    spells.emplace("ray", new Ray(*scenario, 10, 1, 50));
}

TowerDefenseGame::~TowerDefenseGame(){
    delete scenario;

    for (auto& tower_factory : towers_factory) {
        delete tower_factory.second;
    }

    for (auto& spell : spells) {
        delete spell.second;
    }
}

//region Loading_Configuration
void TowerDefenseGame::loadScenarioProperties(YAML::Node& map) {
    name = map["name"].as<std::string>();
    setting = map["setting"].as<std::string>();

    std::vector<Vector> firm_ground_locations;
    YAML::Node firm_g = map["firm_ground"];
    for (YAML::const_iterator it = firm_g.begin(); it != firm_g.end(); ++it ) {
        firm_ground_locations.push_back(it->as<Vector>());
    }

    std::vector<Vector> road;
    YAML::Node paths = map["paths"];
    for (YAML::const_iterator path = paths.begin(); path != paths.end(); ++path ) {
        for (YAML::const_iterator it = path->begin(); it != path->end(); ++it) {
            road.push_back(it->as<Vector>());
        }
    }

    Path path(std::move(road));
    scenario = new Scenario(std::move(path), std::move(firm_ground_locations));
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

void TowerDefenseGame::loadTowerProperties(YAML::Node& properties) {
    tower_properties = properties;
    towers_factory.emplace("fire", new FireTowerFactory());
    towers_factory.emplace("water", new WaterTowerFactory());
    towers_factory.emplace("earth", new EarthTowerFactory());
    towers_factory.emplace("air", new AirTowerFactory());
}
//endregion

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

const Tower& TowerDefenseGame::addTower(const Player &player,
                                        const std::string &type, const Vector &position) {
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
        throw TowerError("Error: el tipo de torre " +
                                 type + " no es un tipo valido");
    }
}

const Player& TowerDefenseGame::addPlayer(const std::string &name,
                                          const std::string& element) {
    if (players.size() == 4) { throw MatchError("Error al añadir jugador: " +
                                                       name + ": partida llena");}
    players.emplace_back(name, element);
    return players.back();
}

void TowerDefenseGame::performeAttacks() {
    for (auto& spell : spells) {
        if (spell.second->isActive()) {
            spell.second->attack();
        }
    }

    for (auto& tower: scenario->getTowers()){
        tower->attack();
    }
}

void TowerDefenseGame::levelupTower(const Tower& tower,
                                    const std::string& type) {
    scenario->levelupTower(tower, type);
}

void TowerDefenseGame::updateGame() {
    performeAttacks();
    scenario->cleanEnemies();
}

void TowerDefenseGame::throwSpell(const Player& player,
                                  const std::string &type,
                                  const Vector& position) {
    Spell* spell = spells.at(type);
    bool can_be_thrown = false;
    for (auto& element : player.getElements()) {
        if (spell->canBeThrownBy(element)) { can_be_thrown = true; break; }
    }

    if (!can_be_thrown) {
        throw MatchError("Error al lanzar hechizo: " +
                         type +
                         " el jugador " +
                         player.getName() +
                         " no posee el elemento adecuado");
    }

    spell->applyEffect(position);
}

void TowerDefenseGame::throwSpell(const Player &player, const std::string &type,
                                  int enemy_id) {
    Spell* spell = spells.at(type);
    bool can_be_thrown = false;
    for (auto& element : player.getElements()) {
        if (spell->canBeThrownBy(element)) { can_be_thrown = true; break; }
    }

    if (!can_be_thrown) {
        throw MatchError("Error al lanzar hechizo: " +
                         type +
                         " el jugador " +
                         player.getName() +
                         " no posee el elemento adecuado");
    }

    for (Enemy& enemy : scenario->getAllEnemies()) {
        if (enemy.getID() == enemy_id) {
            spell->applyEffect(enemy);
            return;
        }
    }
    throw MatchError("Error al lanzar hechizo: " +
                     type +
                     " el enemigo con id " +
                     std::to_string(enemy_id) +
                     " no existe");
}

const std::string &TowerDefenseGame::getGameName() {
    return name;
}

const std::string &TowerDefenseGame::getGameSetting() {
    return setting;
}
