//
// Created by facundo on 10/10/17.
//

#include "Tower.h"

Tower::Tower(int id, Vector position, const YAML::Node& properties,
             Scenario& scenario) : experience(0), id(id),
                                   properties(properties),
                                   scenario(scenario),
                                   position(position) {}

Tower::~Tower() {
    for (auto levelup_type : levelup_types){
        delete levelup_type.second;
    }
}

double Tower::getExperience() const {
    return experience;
}

const Vector &Tower::getPosition() const {
    return position;
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
            damage_dealed_to_current_target = 0;
        }
    } else {
        // si no hay target
        current_target = enemies[0];
        damage_dealed_to_current_target = 0;
    }
}

const Range &Tower::getRange() const {
    return range;
}

void Tower::levelup(const std::string &type) {
   levelup_types.at(type)->levelup();
}

unsigned int Tower::getDamage() const {
    return dmg;
}

void Tower::hitCurrentTarget(unsigned int dmg) {
    unsigned int dmg_dealed = current_target->reduceLife(dmg);
    damage_dealed_to_current_target += dmg_dealed;
    experience += dmg_dealed;

    if (current_target->isDead()) {
        experience += 0.5 * damage_dealed_to_current_target;
    }
}

Tower::Tower(Tower&& other) noexcept : properties(properties), scenario(scenario) {
    this->id = other.id;
    this->experience = other.experience;
    this->position = other.position;
    this->dmg = other.dmg;
    this->range = other.range;
    this->attack_cooldown = other.attack_cooldown;
    this->last_attack_time = other.last_attack_time;
    this->current_target = other.current_target;
    other.current_target = nullptr;
    this->damage_dealed_to_current_target = other.damage_dealed_to_current_target;
    this->range_level = other.range_level;
    this->dmg_level = other.dmg_level;
    this->levelup_types = std::move(other.levelup_types);
}
