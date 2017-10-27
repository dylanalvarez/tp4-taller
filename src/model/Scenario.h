//
// Created by facundo on 15/10/17.
//

#ifndef TOWERDEFENSE_SCENARIO_H
#define TOWERDEFENSE_SCENARIO_H

#include <yaml-cpp/yaml.h>
#include "Enemy.h"
#include "Range.h"
#include "Towers/Tower.h"

class Scenario {
public:
    Scenario(Path&& path, std::vector<Vector>&& firm_ground_locations);
    Scenario(std::vector<Path>&& paths,
             std::vector<Vector>&& firm_ground_locations);
    ~Scenario();

    void addEnemy(Enemy& enemy);

    // añade una torre en la posicion que ella contiene
    // Pre: la posicion debe ser terreno firme
    void addTower(Tower* tower);

    // añade terreno firme en la posicion indicada
    // Pre: la posicion debe ser valida (no ser camino, puerta, etc.)
    void addFirmGround(const Vector& position);

    // levelea la torre con el id pasado
    // Pre: la torre debe tener la exp necesaria y
    // la torre debe existir
    void levelupTower(const Tower&, const std::string& type);

    // remueve los enemigos muertos
    void cleanEnemies();

    // retorna los n primeros enemigos dentro del rango
    // cuando es -1 retorna todos los que esten en rango
    std::vector<Enemy*> getEnemiesInRange(const Range &range, int n = -1);

    std::vector<Enemy>& getAllEnemies();

    std::vector<Tower*>& getTowers();

    Path& getPath(unsigned int number = 1);

    Scenario(const Scenario&) = delete;
    Scenario& operator=(const Scenario&) = delete;
    Scenario(Scenario&&) noexcept;
    Scenario& operator=(Scenario&&) noexcept;

private:
    std::vector<Enemy> enemies;
    std::vector<Tower*> towers;
    std::vector<Vector> firm_ground_locations;
    std::vector<Path> paths;
};


#endif //TOWERDEFENSE_SCENARIO_H
