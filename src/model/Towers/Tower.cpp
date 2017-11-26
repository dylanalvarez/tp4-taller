#include "Tower.h"
#include "../Exceptions/TowerError.h"

Tower::Tower(int id, Vector position, Scenario &scenario) :
        id(id),
        experience(0),
        position(position),
        scenario(scenario) {
    is_attacking = false;
}

Tower::~Tower() {
    for (auto levelup_type : levelup_types) {
        delete levelup_type.second;
    }
}

double Tower::getExperience() const {
    return experience;
}

const Vector &Tower::getPosition() const {
    return position;
}

bool
Tower::isCurrentTargetOutOfRange(const std::vector<Enemy *> &enemies) const {
    for (Enemy *enemy : enemies) {
        if (enemy == current_target) {
            return false;
        }
    }
    return true;
}

void Tower::changeTarget(const std::vector<Enemy *> &enemies) {
    if (current_target) {
        if (current_target->isDead()
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
    try {
        levelup_types.at(type)->levelup();
    } catch (std::exception &e) {
        throw TowerError("Error: el tipo de upgrade " + type + " no existe");
    }
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

Tower::Tower(Tower &&other) noexcept : scenario(other.scenario) {
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

int Tower::getRangeLevel() const {
    return range_level;
}

int Tower::getDamageLevel() const {
    return dmg_level;
}

int Tower::getID() const {
    return id;
}

Communication::Tower::EnemySlowdown Tower::getslowdown() const {
    return Communication::Tower::EnemySlowdown {0, 0};
}

int Tower::getExplosionRange() const {
    return 0;
}

bool Tower::operator==(const Tower &other) {
    return this->id == other.id;
}

int Tower::getRangeInTileSizes(float range) {
    return (int) std::roundf(44 + range * 88);
}

bool Tower::isAttacking() const {
    return is_attacking;
}

int Tower::getCurrentTargetID() const {
    if (current_target) {
        return current_target->getID();
    }

    return -1;
}
