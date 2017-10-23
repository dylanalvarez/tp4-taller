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

class TowerDefenseGame {
public:
    TowerDefenseGame(const std::string& config_file,
                     const std::string& scenario_file);
    ~TowerDefenseGame();

    /*** Enemies ***/

    // añade un enemigo de tipo enemy_type
    // Pre: el tipo debe ser valido
    void addEnemy(const std::string& enemy_type);

    const std::vector<Enemy>& getAllEnemies() const;

    /*** Towers ***/

    // añade la torre de tipo type en la posicion position
    // retorna el id
    const Tower& addTower(const Player& player, const std::string& type,
                            const Vector& position);

    // levelea la torre con el id pasado
    // Pre: la torre debe tener la exp necesaria y
    // la torre debe existir
    void levelupTower(const Tower&, const std::string& type);

    /*** Players ***/

    // añade un jugador a la partida
    // Pre: existen menos de 4 jugadores en la partida
    const Player& addPlayer(const std::string &name,
                            const std::string& element);

    /*** Spells ***/
    void throwSpell(const Player& player, const std::string &type,
                    const Vector& position);

    // lanza el hechizo sobre el enemigo con id enemy_id
    // Pre: debe existir un enemigo con id enemy_id
    void throwSpell(const Player& player, const std::string& type,
                    int enemy_id);

    /*** Metodos que actualizan el estado del juego ***/

    // mueve todos los enemigos
    void moveEnemies();
    // realiza los ataques
    void performeAttacks();

    // llama a moveEnemies y performe attacks ademas de limpiar
    // los enemigos muertos
    void updateGame();

    TowerDefenseGame(const TowerDefenseGame&) = delete;
    TowerDefenseGame& operator=(const TowerDefenseGame&) = delete;
    TowerDefenseGame(TowerDefenseGame&&) = delete;
    TowerDefenseGame& operator=(TowerDefenseGame&&) = delete;

private:
    int tower_id;
    int enemy_id;
    Scenario* scenario;
    std::vector<Player> players;

    YAML::Node tower_properties;

    void loadEnemyProperties(YAML::Node&);
    void loadTowerProperties(YAML::Node&);
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
