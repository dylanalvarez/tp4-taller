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
    explicit Scenario(Path path);

    void addEnemy(int id, std::string enemy_type);

    // retorna los n primeros enemigos dentro del rango
    std::vector<Enemy*> getEnemiesInRange(const Range &range, int n);

    Scenario(const Scenario&) = delete;
    Scenario& operator=(const Scenario&) = delete;
    Scenario(Scenario&&) noexcept;
    Scenario& operator=(Scenario&&) noexcept;

private:
    std::vector<Enemy> enemies;
    Path path;
};


#endif //TOWERDEFENSE_SCENARIO_H
