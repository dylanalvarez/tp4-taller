//
// Created by facundo on 10/10/17.
//

#include <iostream>
#include "FireTower.h"
#include "../Scenario.h"
#include "../Exceptions/TowerError.h"
#include "../Upgrades/DamageLevelup.h"
#include "../Upgrades/ReachLevelup.h"

FireTower::FireTower(int id, const Vector position, const YAML::Node& properties,
                     Scenario& scenario) :
        Tower(id, position, properties, scenario) {

    range_level = 1;
    dmg_level = 1;
    reach_level = 1;

    dmg = 6;
    dmg_to_nearby_units = 3;
    reach_of_impact = 1;
    range = Range(position, 3);

    // un ataque cada 3 segundos
    attack_cooldown = 3;
    last_attack_time = 0;
    current_target = nullptr;
    experience = 0;

    levelup_types.emplace("range", new RangeLevelup(*this));
    levelup_types.emplace("damage", new DamageLevelup(*this));
    levelup_types.emplace("reach", new ReachLevelup(*this));
}

FireTower::~FireTower() = default;

void FireTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    //if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    //{ return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(range);
    if (enemies.empty()) { return; }

    changeTarget(enemies);
    hitCurrentTarget(dmg);

    // daño a los enemigos cercanos
    for (int i = 1; i < enemies.size(); i++) {
        if ((enemies[i]->getCurrentPosition() -
             enemies[0]->getCurrentPosition()).getNorm() <=
                reach_of_impact) {
            // si estan al alcance del impacto
            experience += enemies[i]->reduceLife(dmg_to_nearby_units);
        }
    }

    last_attack_time = time(nullptr);
}

FireTower::FireTower(FireTower&& other) noexcept : Tower(std::move(other)) {}

void FireTower::levelupRange() {
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

void FireTower::levelupDamage() {
    double neccessary_exp = 100 * (pow(1.5,dmg_level));
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));
    }
    dmg += 6;
    dmg_to_nearby_units += 3;
    experience -= neccessary_exp;
    dmg_level++;
}

void FireTower::levelupReachOfImpact() {
    double neccessary_exp = 500 * (pow(2,reach_level));
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));

    }
    reach_of_impact++;
    experience -= neccessary_exp;
    reach_level++;
}

int FireTower::getReachOfImpact() const {
    return reach_of_impact;
}

void FireTower::levelupSlowdown() {}
