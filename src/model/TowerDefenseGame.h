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

class TowerDefenseGame {
public:
    TowerDefenseGame(const std::string& config_file,
                     const std::string& scenario_file);
    ~TowerDefenseGame();

    // añade un enemigo de tipo enemy_type
    // Pre: el tipo debe ser valido
    void addEnemy(const std::string& enemy_type);

    // añade la torre de tipo type en la posicion position
    void addTower(const Player& player, const std::string& type,
     const Vector& position);

    // añade un jugador a la partida
    // Pre: existen menos de 4 jugadores en la partida
    const Player& addPlayer(const std::string& name);

    // mueve todos los enemigos
    void moveEnemies();

    const std::vector<Enemy>& getAllEnemies() const;

private:
    int tower_id;
    Scenario* scenario;
    std::vector<Player> players;

    void loadEnemyProperties(YAML::Node&);
    bool doesPlayerExist(const Player& player);
private:
    // estructura utilizada para guardar las propiedades de un enemigo
    struct EnemyProperties {
        unsigned int hp;
        unsigned int speed;
        bool does_it_fly;

        EnemyProperties(unsigned int hp, unsigned int speed, bool does_it_fly) {
            this->hp = hp;
            this->speed = speed;
            this->does_it_fly = does_it_fly;
        }
    };

    std::map<std::string, EnemyProperties> enemies_properties;
};


#endif //TOWERDEFENSE_TOWERDEFENSEGAME_H
