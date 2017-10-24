//
// Created by facundo on 20/10/17.
//

#include "WaterTower.h"
#include "../Scenario.h"
#include "../Exceptions/TowerError.h"
#include "../Upgrades/DamageLevelup.h"
#include "../Upgrades/SlowdownLevelup.h"

WaterTower::WaterTower(int id, Vector position,
                       YAML::Node &properties, Scenario &scenario) :
        Tower(id, position, properties, scenario) {
    range_level = 1;
    dmg_level = 1;
    slowdown_level = 1;

    attack_cooldown = 3;
    last_attack_time = 0;
    current_target = nullptr;
    experience = 0;

    dmg = 4;
    speed_reduction = 25;
    speed_reduction_duration = 2;
    range = Range(position, 3);

    levelup_types.emplace("range", new RangeLevelup(*this));
    levelup_types.emplace("damage", new DamageLevelup(*this));
    levelup_types.emplace("slowdown", new SlowdownLevelup(*this));
}

WaterTower::~WaterTower() = default;

void WaterTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    //if (difftime(time(nullptr), last_attack_time) < attack_cooldown) { return; }

    std::vector<Enemy*> enemies = std::move(scenario.getEnemiesInRange(range));
    if (enemies.empty()) { return; }

    changeTarget(enemies);
    hitCurrentTarget(dmg);
    current_target->reduceSpeed(speed_reduction, speed_reduction_duration);

    last_attack_time = time(nullptr);
}

WaterTower::WaterTower(WaterTower&& other) noexcept : Tower(std::move(other)) {}

void WaterTower::levelupRange() {
    double neccessary_exp = 100 * (pow(2,range_level));
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

void WaterTower::levelupDamage() {
    double neccessary_exp = 100 * (pow(1.5,dmg_level));
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));
    }
    dmg += 4;
    experience -= neccessary_exp;
    dmg_level++;
}

void WaterTower::levelupSlowdown() {
    double neccessary_exp = 100 * (pow(2,slowdown_level));
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));
    }

    if (speed_reduction >= 100) {
        speed_reduction_duration++;
    } else {
        speed_reduction += 25;
    }
    experience -= neccessary_exp;
    slowdown_level++;
}

void WaterTower::levelupReachOfImpact() {}
