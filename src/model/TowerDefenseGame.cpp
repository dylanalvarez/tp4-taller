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
                                   const std::string &scenario_file,
                                   int enemy_count) {
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
    this->enemy_count = enemy_count;
    is_game_over = false;

    players.reserve(MAX_PLAYERS);

    available_elements.emplace_back("air");
    available_elements.emplace_back("water");
    available_elements.emplace_back("fire");
    available_elements.emplace_back("earth");
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
    for (auto it = firm_g.begin(); it != firm_g.end(); ++it ) {
        firm_ground_locations.push_back(it->as<Vector>());
    }

    std::vector<Path> paths;
    YAML::Node paths_node = map["paths"];
    for (auto path = paths_node.begin(); path != paths_node.end(); ++path ) {
        // se busca el nodo "path_sequence"
        YAML::Node path_secuence = (*path)["path_sequence"];

        std::vector<Vector> road;
        for (auto it = path_secuence.begin(); it != path_secuence.end(); ++it) {
            road.push_back(it->as<Vector>());
        }
        paths.emplace_back(Path(std::move(road)));
    }

    scenario = new Scenario(std::move(paths), std::move(firm_ground_locations));
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
    spells.emplace("fireWall", new FireWall(*scenario,
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
    spells.emplace("tornado", new Tornato(*scenario,
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
                               green_demon_node["speed"].as<float>(),
                               green_demon_node["fly"].as<bool>());
    enemies_properties.emplace("green_demon", gd_properties);

    YAML::Node abmonible_node = enemies_node["abmonible"];
    EnemyProperties ab_properties(abmonible_node["health"].as<unsigned int>(),
                               abmonible_node["speed"].as<float>(),
                               abmonible_node["fly"].as<bool>());
    enemies_properties.emplace("abmonible", ab_properties);

    YAML::Node goat_man_node = enemies_node["goat_man"];
    EnemyProperties gm_properties(goat_man_node["health"].as<unsigned int>(),
                                  goat_man_node["speed"].as<float>(),
                                  goat_man_node["fly"].as<bool>());
    enemies_properties.emplace("goat_man", gm_properties);

    YAML::Node undead_node = enemies_node["undead"];
    EnemyProperties u_properties(undead_node["health"].as<unsigned int>(),
                                 undead_node["speed"].as<float>(),
                                 undead_node["fly"].as<bool>());
    enemies_properties.emplace("undead", u_properties);

    YAML::Node bloody_hawk_node = enemies_node["bloody_hawk"];
    EnemyProperties bh_properties(bloody_hawk_node["health"].as<unsigned int>(),
                                  bloody_hawk_node["speed"].as<float>(),
                                  bloody_hawk_node["fly"].as<bool>());
    enemies_properties.emplace("bloody_hawk", bh_properties);

    YAML::Node spectrum_node = enemies_node["spectrum"];
    EnemyProperties s_properties(spectrum_node["health"].as<unsigned int>(),
                                 spectrum_node["speed"].as<float>(),
                                 spectrum_node["fly"].as<bool>());
    enemies_properties.emplace("spectre", s_properties);
}

void TowerDefenseGame::loadTowerProperties(YAML::Node& properties) {
    tower_properties = properties;
    towers_factory.emplace("fire", new FireTowerFactory());
    towers_factory.emplace("water", new WaterTowerFactory());
    towers_factory.emplace("earth", new EarthTowerFactory());
    towers_factory.emplace("air", new AirTowerFactory());
}
//endregion

void TowerDefenseGame::addEnemy(const std::string &enemy_type,
                                unsigned int path_number) {
    try{
        EnemyProperties properties = enemies_properties.at(enemy_type);
        Enemy enemy(enemy_id++, scenario->getPath(path_number), properties.hp,
                    properties.speed, properties.does_it_fly, enemy_type);
        scenario->addEnemy(enemy);
    } catch (std::exception& e) {
        throw EnemyError("Error al agregar enemigo -> El tipo: " + enemy_type
                         + " no es un tipo valido");
    }
}

const std::vector<Enemy> &TowerDefenseGame::getAllEnemies() const {
    return scenario->getAllEnemies();
}

void TowerDefenseGame::moveEnemies(int units_to_move) {
    for (Enemy& enemy : scenario->getAllEnemies()){
        enemy.move(units_to_move);
        if (enemy.reachTheEnd()) { is_game_over = true; }
    }
}

bool TowerDefenseGame::doesPlayerExist(const Player &player) {
    for (Player& p : players) {
        if (&p == &player) {
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
    Tower* tower = nullptr;
    try {
        tower = towers_factory.at(type)->create(tower_id++, position,
                                                tower_properties, *scenario);
    } catch (std::out_of_range& e) {
            throw TowerError("Error: el tipo de torre " +
                             type + " no es un tipo valido");
    }

    if (player.canBuildTower(type)) {
        try {
            scenario->addTower(tower);
        } catch (TowerError& e) {
            delete tower;
            throw e;
        }
        for (Player& p : players) {
            if (&p == &player) {
                p.addTower(*tower);
            }
        }
        return *tower;
    } else {
        delete tower;
        throw MatchError("Error: el jugador " + player.getName()
                         + "no puede construir torres de tipo " + type);
    }
}

const Player& TowerDefenseGame::addPlayer(std::string name,
                                          std::string element) {
    if (players.size() == MAX_PLAYERS) {
        throw MatchError("Error al añadir jugador: " +
                         name + ": partida llena");
    }

    if (std::find(available_elements.begin(), available_elements.end(),
                  element) == available_elements.end()) {
        throw MatchError("Error al añadir jugador: " +
                         name + ": el elemento" + element + "no esta disponible");
    }
    available_elements.erase(std::remove(available_elements.begin(),
                                         available_elements.end(), element));
    players.emplace_back(std::move(name), std::move(element));
    return players.back();
}

const Player &TowerDefenseGame::addPlayer(std::string name) {
    if (players.size() == MAX_PLAYERS) {
        throw MatchError("Error al añadir jugador: " +
                         name + ": partida llena");
    }

    players.emplace_back(std::move(name));
    return players.back();
}

void TowerDefenseGame::addElementToPlayer(const Player &player,
                                          const std::string &element) {
    if (std::find(available_elements.begin(), available_elements.end(),
                  element) == available_elements.end()) {
        throw MatchError("Error al añadir elemento al jugador: " +
                         player.getName() +
                         ", el elemento" + element + "no esta disponible");
    }

    available_elements.erase(std::remove(available_elements.begin(),
                                         available_elements.end(), element));

    for (Player& p : players) {
        if (&p == &player) {
            p.addElement(element);
        }
    }
}

void TowerDefenseGame::performAttacks() {
    for (auto& spell : spells) {
        if (spell.second->isActive()) {
            spell.second->update();
        }
    }

    for (auto& tower: scenario->getTowers()){
        tower->attack();
    }
}

void TowerDefenseGame::levelupTower(const Tower& tower,
                                    const std::string& type,
                                    const Player& player) {
    if (!player.containsTower(tower)) {
        throw MatchError("Error: el jugador" +
                                 player.getName() +
                                 "no puede levelear las torres de tipo");
    }
    scenario->levelupTower(tower, type);
}

void TowerDefenseGame::updateGame(int units_to_move) {
    moveEnemies(units_to_move);
    performAttacks();
    enemy_count -= scenario->cleanEnemies();
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

const std::string &TowerDefenseGame::getGameName() const {
    return name;
}

const std::string &TowerDefenseGame::getGameSetting() const {
    return setting;
}

bool TowerDefenseGame::isGameOver() const {
    return is_game_over;
}

Communication::GameState TowerDefenseGame::getGameState() const {
    Communication::GameState gameState{};
    // enemies
    for (const Enemy& enemy : getAllEnemies()) {
        gameState.enemies.emplace_back(
                enemy.getType(),
                enemy.getID(),
                (int)enemy.getCurrentPosition().getX() - 44,
                (int)enemy.getCurrentPosition().getY() - 44
        );
    }

    // towers
    for (const Tower* tower: scenario->getTowers()) {
        Communication::Tower::Level level(tower->getRangeLevel(),
                                          tower->getDamageLevel(),
                                          tower->getReachLevel(),
                                          tower->getSlowDownLevel());
        gameState.towers.emplace_back(
                tower->getID(),
                level,
                (int)tower->getExperience(),
                tower->getRange().getNormalRadius(),
                tower->getExplosionRange(),
                tower->getPosition().getX(),
                tower->getPosition().getY(),
                tower->getslowdown(),
                tower->getDamage_(),
                tower->getType(),
                tower->isAttacking(),
                tower->getCurrentTargetID()
        );
    }

    // positional powers
    for (auto& spell: spells) {
        if (spell.second->isActive()) {
            if (spell.second->isPositional()){
                gameState.positionalPowers.emplace_back(
                        spell.second->getPositionalType(),
                        (int)spell.second->getPosition().getX(),
                        (int)spell.second->getPosition().getY()
                );
            } else {
                gameState.targetPowers.emplace_back(
                        spell.second->getTargetType(),
                        spell.second->getTargetID()
                );
            }
        }
    }

    if (isGameOver()) {
        gameState.state = Communication::GameState::State::lost;
    } else if (enemy_count == 0) {
        gameState.state = Communication::GameState::State::won;
    } else { gameState.state = Communication::GameState::State::ongoing; }

    return gameState;
}

bool TowerDefenseGame::isGameEnded() const {
    return (is_game_over || (enemy_count <= 0));
}

std::vector<std::string> TowerDefenseGame::getNotAvailableElements() const {
    std::vector<std::string> available = {"air", "earth", "fire", "water"};

    for (const std::string& element : available_elements) {
        available.erase(std::remove(available.begin(), available.end(),
                                    element));
    }

    return available;
}
