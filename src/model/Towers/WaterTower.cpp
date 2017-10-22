//
// Created by facundo on 20/10/17.
//

#include "WaterTower.h"
#include "../Scenario.h"

WaterTower::WaterTower(int id, Vector position,
                       const YAML::Node &properties, Scenario &scenario) :
        Tower(id, position, properties, scenario) {
    dmg = 4;
    range = Range(position, 3);
    attack_cooldown = 3;
    last_attack_time = 0;
    current_target = nullptr;
    speed_reduction = 25;
    speed_reduction_time = 2;
}

WaterTower::~WaterTower() = default;

void WaterTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    if (difftime(time(nullptr), last_attack_time) < attack_cooldown) { return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(range);
    if (enemies.empty()) { return; }

    changeTarget(enemies);

    current_target->reduceLife(dmg);
    current_target->reduceSpeed(speed_reduction, speed_reduction_time);

    last_attack_time = time(nullptr);
}

WaterTower::WaterTower(WaterTower&& other) noexcept : Tower(std::move(other)) {
    this->speed_reduction = other.speed_reduction;
    this->speed_reduction_time = other.speed_reduction_time;
}
