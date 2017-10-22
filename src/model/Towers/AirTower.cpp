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

    changeTarget(enemies);

    // TODO sacar este if con clase Damage
    if (current_target->canIFlight()){
        current_target->reduceLife(dmg_to_flying_units);
    } else {
        current_target->reduceLife(dmg);
    }

    // la torre de aire hace retroceder al enemigo
    current_target->move_back();

    last_attack_time = time(nullptr);
}

AirTower::AirTower(AirTower&& other) noexcept : Tower(std::move(other)) {
    this->dmg_to_flying_units = other.dmg_to_flying_units;
}
