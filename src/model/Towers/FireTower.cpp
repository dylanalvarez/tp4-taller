//
// Created by facundo on 10/10/17.
//

#include <iostream>
#include "FireTower.h"
#include "../Scenario.h"

FireTower::FireTower(int id, const Vector position, const YAML::Node& properties,
                     Scenario& scenario) :
        Tower(id, position, properties, scenario) {
    range = Range(position, 3);
    dmg = 6;
    dmg_to_nearby_enemies = 3;
    // un ataque cada 3 segundos
    attack_cooldown = 3;
    last_attack_time = 0;
    current_target = nullptr;
}

FireTower::~FireTower() = default;

void FireTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    { return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(range);
    if (enemies.empty()) { return; }

    // si el current_objective no esta en la lista, entonces no esta en rango
    bool is_out_of_range = true;
    for (Enemy* enemy : enemies){
        if (enemy == current_target){
            is_out_of_range = false;
        }
    }

    if (current_target) {
        if (current_target->getHealthPoints() == 0 || is_out_of_range){
            // si hay target pero esta muerto
            current_target = enemies[0];
        }
    } else {
        // si no hay target
        current_target = enemies[0];
    }

    current_target->reduceLife(dmg);

    // daño a los enemigos cercanos
    for (int i = 1; i < enemies.size(); i++) {
        if ((enemies[i]->getCurrentPosition() -
                enemies[0]->getCurrentPosition()).getNorm() <= 1){
            // si estan a distancia 1
            enemies[i]->reduceLife(dmg_to_nearby_enemies);
        }
    }

    last_attack_time = time(nullptr);
}

FireTower::FireTower(FireTower&& other) noexcept : Tower(std::move(other)) {
    this->dmg_to_nearby_enemies = other.dmg_to_nearby_enemies;
}
