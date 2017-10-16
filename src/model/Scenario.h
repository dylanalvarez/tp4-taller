//
// Created by facundo on 15/10/17.
//

#ifndef TOWERDEFENSE_SCENARIO_H
#define TOWERDEFENSE_SCENARIO_H

#include <yaml-cpp/yaml.h>
#include "Enemy.h"
#include "Range.h"

class Scenario {
public:
    Scenario(Path path, YAML::Node config);

    // añade un enemigo con la identificacion determinada por id
    // Pre: no existe otro enemigo con el mismo id, y enemy_type
    // es un tipo valido
    void addEnemy(int id, std::string enemy_type);

    // retorna los n primeros enemigos dentro del rango
    std::vector<Enemy*> getEnemiesInRange(const Range &range, int n);

    std::vector<Enemy>& getAllEnemies();

    Scenario(const Scenario&) = delete;
    Scenario& operator=(const Scenario&) = delete;
    Scenario(Scenario&&) noexcept;
    Scenario& operator=(Scenario&&) noexcept;

private:
    std::vector<Enemy> enemies;
    Path path;

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


#endif //TOWERDEFENSE_SCENARIO_H
