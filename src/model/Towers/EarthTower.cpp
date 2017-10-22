//
// Created by facundo on 21/10/17.
//

#include "EarthTower.h"
#include "../Scenario.h"

EarthTower::EarthTower(int id, Vector p, const YAML::Node &properties,
                       Scenario &scneario) :
        Tower(id, p, properties, scneario) {
    this->dmg = 20;
    this->range = Range(position, 2);
    this->last_attack_time = 0;
    this->attack_cooldown = 5;
    this->current_target = nullptr;
}

EarthTower::~EarthTower() = default;

void EarthTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    { return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(range);
    if (enemies.empty()) { return; }

    if (current_target) {
        if (current_target->getHealthPoints() == 0
            || isCurrentTargetOutOfRange(enemies)){
            // si hay target pero esta muerto
            // o esta fuera de rango
            current_target = getNotFlyingEnemy(enemies);
        }
    } else {
        // si no hay target
        current_target = getNotFlyingEnemy(enemies);
    }

    if (!current_target) { return; } // si no encontro ninguno que no vuele salir

    current_target->reduceLife(dmg);

    last_attack_time = time(nullptr);
}

EarthTower::EarthTower(EarthTower&& other) noexcept :
        Tower(std::move(other)) {}

Enemy *EarthTower::getNotFlyingEnemy(const std::vector<Enemy *>& enemies) {
    for (Enemy* enemy : enemies){
        if (!enemy->canIFlight()) { return enemy; }
    }
    return nullptr;
}
