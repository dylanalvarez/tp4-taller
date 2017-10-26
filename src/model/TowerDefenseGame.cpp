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

    YAML::Node towers_node = config["towers"];
    YAML::Node enemies_node = config["enemies"];
    YAML::Node spells_node = config["spells"];

    loadEnemyProperties(enemies_node);
    loadTowerProperties(towers_node);
    loadScenarioProperties(map);
    loadSpellsProperties(spells_node);

    tower_id = 1;
    enemy_id = 1;
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

void TowerDefenseGame::loadSpellsProperties(YAML::Node& spells_node) {
    YAML::Node terraforming = spells_node["terraforming"];
    spells.emplace("terraforming", new Terraforming(*scenario,
                                                    terraforming["cooldown"].as<unsigned int>()));
    YAML::Node fissure = spells_node["fissure"];
    spells.emplace("fissure", new Fissure(*scenario,
                                      fissure["cooldown"].as<unsigned int>(),
                                      fissure["duration"].as<unsigned int>()));
    YAML::Node meteorite = spells_node["meteorite"];
    spells.emplace("meteorite", new Meteorite(*scenario,
                                          meteorite["cooldown"].as<unsigned int>(),
                                          meteorite["reach_of_impact"].as<unsigned int>(),
                                          meteorite["damage"].as<unsigned int>(),
                                          meteorite["damage_to_nearby_units"].as<unsigned int>()));
    YAML::Node fire_wall = spells_node["fire_wall"];
    spells.emplace("fire_wall", new FireWall(*scenario,
                                         fire_wall["cooldown"].as<unsigned int>(),
                                         fire_wall["damage"].as<unsigned int>(),
                                         fire_wall["duration"].as<unsigned int>()));
    YAML::Node freezing = spells_node["freezing"];
    spells.emplace("freezing", new Freezing(*scenario,
                                            freezing["cooldown"].as<unsigned int>(),
                                            freezing["duration"].as<unsigned int>()));
    YAML::Node blizzard = spells_node["blizzard"];
    spells.emplace("blizzard", new Blizzard(*scenario,
                                            blizzard["cooldown"].as<unsigned int>(),
                                            blizzard["duration"].as<unsigned int>(),
                                            blizzard["damage"].as<unsigned int>(),
                                            blizzard["slowdown"].as<unsigned int>(),
                                            blizzard["slowdown_duration"].as<unsigned int>()));
    YAML::Node tornado = spells_node["tornado"];
    spells.emplace("tornato", new Tornato(*scenario,
                                          tornado["cooldown"].as<unsigned int>(),
                                          tornado["min_damage"].as<unsigned int>(),
                                          tornado["max_damage"].as<unsigned int>(),
                                          tornado["duration"].as<unsigned int>()));
    YAML::Node ray = spells_node["ray"];
    spells.emplace("ray", new Ray(*scenario,
                                  ray["cooldown"].as<unsigned int>(),
                                  ray["min_damage"].as<unsigned int>(),
                                  ray["max_damage"].as<unsigned int>()));
}

void TowerDefenseGame::loadEnemyProperties(YAML::Node& enemies_node) {
    YAML::Node green_demon_node = enemies_node["green_demon"];
    EnemyProperties gd_properties(green_demon_node["health"].as<unsigned int>(),
                               green_demon_node["speed"].as<unsigned int>(),
                               green_demon_node["fly"].as<bool>());
    enemies_properties.emplace("green_demon", gd_properties);

    YAML::Node abmonible_node = enemies_node["abmonible"];
    EnemyProperties ab_properties(abmonible_node["health"].as<unsigned int>(),
                               abmonible_node["speed"].as<unsigned int>(),
                               abmonible_node["fly"].as<bool>());
    enemies_properties.emplace("abmonible", ab_properties);

    YAML::Node goat_man_node = enemies_node["goat_man"];
    EnemyProperties gm_properties(goat_man_node["health"].as<unsigned int>(),
                                  goat_man_node["speed"].as<unsigned int>(),
                                  goat_man_node["fly"].as<bool>());
    enemies_properties.emplace("goat_man", gm_properties);

    YAML::Node undead_node = enemies_node["undead"];
    EnemyProperties u_properties(undead_node["health"].as<unsigned int>(),
                                 undead_node["speed"].as<unsigned int>(),
                                 undead_node["fly"].as<bool>());
    enemies_properties.emplace("undead", u_properties);

    YAML::Node bloody_hawk_node = enemies_node["bloody_hawk"];
    EnemyProperties bh_properties(bloody_hawk_node["health"].as<unsigned int>(),
                                  bloody_hawk_node["speed"].as<unsigned int>(),
                                  bloody_hawk_node["fly"].as<bool>());
    enemies_properties.emplace("bloody_hawk", bh_properties);

    YAML::Node spectrum_node = enemies_node["spectrum"];
    EnemyProperties s_properties(spectrum_node["health"].as<unsigned int>(),
                                 spectrum_node["speed"].as<unsigned int>(),
                                 spectrum_node["fly"].as<bool>());
    enemies_properties.emplace("spectrum", s_properties);
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
