//
// Created by facundo on 10/10/17.
//

#include "Tower.h"

Tower::Tower(int id, Vector position, const YAML::Node& properties,
             Scenario& scenario) : experience(0), id(id),
                                   properties(properties),
                                   scenario(scenario),
                                   position(position) {}

Tower::~Tower() = default;

unsigned int Tower::getExperience() const {
    return experience;
}

const Vector &Tower::getPosition() const {
    return position;
}

Tower::Tower(Tower&& other) noexcept : properties(other.properties),
                              scenario(other.scenario) {
    this->id = other.id;
    other.id = 0;

    this->position = other.position;
    this->experience = other.experience;
    this->range = other.range;
    this->dmg = other.dmg;
    this->attack_cooldown = other.attack_cooldown;
    this->last_attack_time = other.last_attack_time;

    this->current_target = other.current_target;
    other.current_target = nullptr;
}

bool Tower::isCurrentTargetOutOfRange(const std::vector<Enemy*>& enemies) const {
    for (Enemy* enemy : enemies){
        if (enemy == current_target){
            return false;
        }
    }
    return true;
}

void Tower::changeTarget(const std::vector<Enemy*>& enemies) {
    if (current_target) {
        if (current_target->getHealthPoints() == 0
            || isCurrentTargetOutOfRange(enemies)) {
            // si hay target pero esta muerto
            // o si se fue de rango
            current_target = enemies[0];
        }
    } else {
        // si no hay target
        current_target = enemies[0];
    }
}
