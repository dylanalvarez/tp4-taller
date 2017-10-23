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
    delete level;

    for (auto& levelup_type : levelup_types){
        delete levelup_type.second;
    }
}

double Tower::getExperience() const {
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
    this->attack_cooldown = other.attack_cooldown;
    this->last_attack_time = other.last_attack_time;
    this->current_target = other.current_target;
    this->level = other.level;

    other.level = nullptr;
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
            damage_dealed_to_current_target = 0;
        }
    } else {
        // si no hay target
        current_target = enemies[0];
        damage_dealed_to_current_target = 0;
    }
}

const Range &Tower::getRange() const {
    return level->getRange();
}

void Tower::levelup(const std::string &type) {
    TowerLevel* new_level = levelup_types.at(type)->levelup(*level, experience);
    experience -= levelup_types.at(type)->getExperienceNeededforLevel(level->getLevel());
    delete level;
    level = new_level;
}

unsigned int Tower::getDamage() const {
    return level->getDamage();
}

void Tower::hitCurrentTarget(unsigned int dmg) {
    unsigned int dmg_dealed = current_target->reduceLife(dmg);
    damage_dealed_to_current_target += dmg_dealed;
    experience += dmg_dealed;

    if (current_target->isDead()) {
        experience += 0.5 * damage_dealed_to_current_target;
    }
}

int Tower::getReachOfImpact() const {
    return level->getReachOfImpact();
}
