//
// Created by facundo on 21/10/17.
//

#include "AirTower.h"
#include "../Scenario.h"

AirTower::AirTower(int id, Vector p, const YAML::Node &properties,
                   Scenario &scneario) :
        Tower(id, p, properties, scneario) {
    this->dmg = 2;
    this->dmg_to_flying_units = 10;
    this->range = Range(position, 5);
    this->last_attack_time = 0;
    this->attack_cooldown = 5;
    this->current_target = nullptr;
}

AirTower::~AirTower() = default;

void AirTower::attack() {
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

    if (current_target->canIFlight()){
        current_target->reduceLife(dmg_to_flying_units);
    } else {
        current_target->reduceLife(dmg);
    }

    current_target->move_back();

    last_attack_time = time(nullptr);
}

AirTower::AirTower(AirTower&& other) noexcept : Tower(std::move(other)) {}
