//
// Created by facundo on 16/10/17.
//

#ifndef TOWERDEFENSE_TOWERDEFENSEGAME_H
#define TOWERDEFENSE_TOWERDEFENSEGAME_H

#include <string>
#include <map>
#include "Path.h"
#include "Scenario.h"

class TowerDefenseGame {
public:
    TowerDefenseGame(const std::string& config_file,
                     const std::string& scenario_file);
    ~TowerDefenseGame();

    // añade un enemigo de tipo enemy_type
    // Pre: el tipo debe ser valido
    void addEnemy(const std::string& enemy_type);

    // mueve todos los enemigos
    void moveEnemies();

    const std::vector<Enemy>& getAllEnemies() const;

private:
    int id;
    Scenario* scenario;

    void loadEnemyProperties(YAML::Node&);

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
