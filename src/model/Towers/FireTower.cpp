//
// Created by facundo on 10/10/17.
//

#include <iostream>
#include "FireTower.h"
#include "../Scenario.h"
#include "../Upgrades/DamageLevelup.h"
#include "../Upgrades/ReachLevelup.h"

static double getNecessaryExpToLevelupRange(int level) {
   return (100 * pow(2, level));
}

static double getNecessaryExpToLevelupDamage(int level) {
    return (100 * pow(1.5, level));
}

static double getNecessaryExpToLevelupReachOfImpact(int level) {
    return (500 * pow(2, level));
}

FireTower::FireTower(int id, const Vector position, const YAML::Node& properties,
                     Scenario& scenario) :
        Tower(id, position, properties, scenario) {

    level = new TowerLevel(1, 6, 6, 3, 1, Range(position, 3), 0, 0);

    // levelea +1 rango
    levelup_types.emplace("range", new RangeLevelup(1,
                                                    &getNecessaryExpToLevelupRange));
    // levelea +6 ataque, +6 contra voladores, +3 contra cercanos
    levelup_types.emplace("damage", new DamageLevelup(6, 6, 3,
                                                      &getNecessaryExpToLevelupDamage));
    // levelea +1 alcance de impacto
    levelup_types.emplace("reach", new ReachLevelup(1,
                                                      &getNecessaryExpToLevelupReachOfImpact));

    // un ataque cada 3 segundos
    attack_cooldown = 3;
    last_attack_time = 0;
    current_target = nullptr;
    experience = 0;
}

FireTower::~FireTower() = default;

void FireTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    //if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    //{ return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(level->getRange());
    if (enemies.empty()) { return; }

    changeTarget(enemies);
    hitCurrentTarget(level->getDamage());

    // daño a los enemigos cercanos
    for (int i = 1; i < enemies.size(); i++) {
        if ((enemies[i]->getCurrentPosition() -
             enemies[0]->getCurrentPosition()).getNorm() <=
                level->getReachOfImpact()) {
            // si estan al alcance del impacto
            experience += enemies[i]->reduceLife(level->getDamageToNearbyUnits());
        }
    }

    last_attack_time = time(nullptr);
}

FireTower::FireTower(FireTower&& other) noexcept : Tower(std::move(other)) {}
