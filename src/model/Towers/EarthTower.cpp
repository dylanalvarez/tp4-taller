//
// Created by facundo on 21/10/17.
//

#include "EarthTower.h"
#include "../Scenario.h"
#include "../Exceptions/TowerError.h"
#include "../Upgrades/DamageLevelup.h"

EarthTower::EarthTower(int id, Vector p, const YAML::Node &properties,
                       Scenario &scneario) :
        Tower(id, p, properties, scneario) {
    range_level = 1;
    dmg_level = 1;
    last_attack_time = 0;
    attack_cooldown = 5;
    current_target = nullptr;
    experience = 0;

    dmg = 20;
    range = Range(position, 2);

    levelup_types.emplace("range", new RangeLevelup(*this));
    levelup_types.emplace("damage", new DamageLevelup(*this));
}

EarthTower::~EarthTower() = default;

void EarthTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    //if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    //{ return; }

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

    hitCurrentTarget(dmg);

    last_attack_time = time(nullptr);
}

EarthTower::EarthTower(EarthTower&& other) noexcept :
        Tower(std::move(other)) {}

Enemy *EarthTower::getNotFlyingEnemy(const std::vector<Enemy *>& enemies) {
    for (Enemy* enemy : enemies){
        if (!enemy->canIFlight() && !enemy->isDead()) {
            damage_dealed_to_current_target = 0;
            return enemy;
        }
    }
    return nullptr;
}

void EarthTower::levelupDamage() {
    double neccessary_exp = 100 * (pow(1.5,dmg_level));
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));
    }

    dmg += 10;
    dmg_level++;
    experience -= neccessary_exp;
}

void EarthTower::levelupRange() {
    double neccessary_exp = 500 * (pow(2,range_level));
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));
    }

    range = Range(position, range.getRadius() + 1);
    experience -= neccessary_exp;
    range_level++;
}

void EarthTower::levelupReachOfImpact() {}

void EarthTower::levelupSlowdown() {}
