//
// Created by facundo on 16/10/17.
//

#ifndef TOWERDEFENSE_TOWERDEFENSEGAME_H
#define TOWERDEFENSE_TOWERDEFENSEGAME_H

#include <string>
#include <map>
#include "Path.h"
#include "Scenario.h"
#include "Player.h"
#include "Factory/TowerFactory.h"
#include "Spells/Spell.h"

#define MAX_PLAYERS 4

class TowerDefenseGame {
public:
    TowerDefenseGame(const std::string& config_file,
                     const std::string& scenario_file,
                     int enemy_count = 0);
    ~TowerDefenseGame();

    /*** Enemies ***/

    // añade un enemigo de tipo enemy_type
    // Pre: el tipo debe ser valido
    void addEnemy(const std::string& enemy_type, unsigned int path_number = 1);

    /*** Towers ***/

    // añade la torre de tipo type en la posicion position
    // retorna el id
    const Tower& addTower(const Player& player, const std::string& type,
                            const Vector& position);

    // levelea la torre con el id pasado
    // Pre: la torre debe tener la exp necesaria y
    // la torre debe existir
    void levelupTower(const Tower&, const std::string& type, const Player& player);

    /*** Players ***/

    // añade un jugador a la partida
    // Pre: existen menos de 4 jugadores en la partida
    const Player& addPlayer(std::string name, std::string element);
    const Player& addPlayer(std::string name);

    void addElementToPlayer(const Player& player, const std::string& element);

    /*** Spells ***/
    void throwSpell(const Player& player, const std::string &type,
                    const Vector& position);

    // lanza el hechizo sobre el enemigo con id enemy_id
    // Pre: debe existir un enemigo con id enemy_id
    void throwSpell(const Player& player, const std::string& type,
                    int enemy_id);

    /*** Metodos que actualizan el estado del juego ***/

    // mueve todos los enemigos
    void moveEnemies(int units_to_move = 1);
    // realiza los ataques (torres y hechizos)
    void performAttacks();
    // llama a moveEnemies y performe attacks ademas de limpiar
    // los enemigos muertos
    void updateGame(int units_to_move = 1);

    /*** Getters ***/

    const std::string& getGameName() const;
    const std::string& getGameSetting() const;
    const std::vector<Enemy>& getAllEnemies() const;
    Communication::GameState getGameState() const;
    std::vector<std::string> getNotAvailableElements() const;

    TowerDefenseGame(const TowerDefenseGame&) = delete;
    TowerDefenseGame& operator=(const TowerDefenseGame&) = delete;
    TowerDefenseGame(TowerDefenseGame&&) = delete ;
    TowerDefenseGame& operator=(TowerDefenseGame&&) = delete;

    // retorna true si se perdio la partida
    bool isGameOver() const;
    
    // retorna true si se termino la partida
    bool isGameEnded() const;

private:
    // nombre de la partida
    std::string name;
    // estilo de mapa (desierto, pradera, etc.)
    std::string setting;

    int tower_id;
    int enemy_id;
    bool is_game_over;
    int enemy_count;
    Scenario* scenario;
    std::vector<Player> players;
    std::vector<std::string> available_elements;
    YAML::Node tower_properties;

    void loadEnemyProperties(YAML::Node&);
    void loadTowerProperties(YAML::Node&);
    void loadScenarioProperties(YAML::Node&);
    void loadSpellsProperties(YAML::Node&);

    bool doesPlayerExist(const Player& player);

private:
    // estructura utilizada para guardar las propiedades de un enemigo
    struct EnemyProperties {
        int hp;
        float speed;
        bool does_it_fly;

        EnemyProperties(int hp, float speed, bool does_it_fly) {
            this->hp = hp;
            this->speed = speed;
            this->does_it_fly = does_it_fly;
        }
    };

    std::map<std::string, EnemyProperties> enemies_properties;
    std::map<std::string, TowerFactory*> towers_factory;
    std::map<std::string, Spell*> spells;
};


#endif //TOWERDEFENSE_TOWERDEFENSEGAME_H
