//
// Created by facundo on 15/10/17.
//

#ifndef TOWERDEFENSE_SCENARIO_H
#define TOWERDEFENSE_SCENARIO_H

#include <yaml-cpp/yaml.h>
#include "Enemy.h"
#include "Range.h"
#include "Tower.h"

class Scenario {
public:
    Scenario(Path&& path, std::vector<Vector>&& firm_ground_locations);
    ~Scenario();

    void addEnemy(Enemy&& enemy);

    void addTower(Tower* tower);

    // retorna los n primeros enemigos dentro del rango
    std::vector<Enemy*> getEnemiesInRange(const Range &range, int n);

    std::vector<Enemy>& getAllEnemies();

    std::vector<Tower*>& getTowers();

    Path& getPath();

    Scenario(const Scenario&) = delete;
    Scenario& operator=(const Scenario&) = delete;
    Scenario(Scenario&&) noexcept;
    Scenario& operator=(Scenario&&) noexcept;

private:
    std::vector<Enemy> enemies;
    std::vector<Tower*> towers;
    std::vector<Vector> firm_ground_locations;
    Path path;
};


#endif //TOWERDEFENSE_SCENARIO_H
