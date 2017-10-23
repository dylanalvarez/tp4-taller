//
// Created by facundo on 20/10/17.
//

#include "WaterTower.h"
#include "../Scenario.h"
#include "../Upgrades/DamageLevelup.h"
#include "../Upgrades/SlowdownLevelup.h"

static double getNecessaryExpToLevelupRange(int level){
    return (100 * (pow(2,level)));
}

static double getNecessaryExpToLevelupDamage(int level) {
    return (100 * pow(1.5, level));
}

static double getNecessaryExpToLevelupSlowDown(int level) {
    return (100 * pow(2, level));
}

WaterTower::WaterTower(int id, Vector position,
                       const YAML::Node &properties, Scenario &scenario) :
        Tower(id, position, properties, scenario) {
    level = new TowerLevel(1, 4, 4, 0, 0, Range(position, 3), 25, 2);
    attack_cooldown = 3;
    last_attack_time = 0;
    current_target = nullptr;
    experience = 0;

    // levelea +1 rango
    levelup_types.emplace("range", new RangeLevelup(1,
                                                    &getNecessaryExpToLevelupRange));
    // levelea +4 ataque, +4 contra voladores, 0 contra cercanos
    levelup_types.emplace("damage", new DamageLevelup(4, 4, 0,
                                                      &getNecessaryExpToLevelupDamage));
    levelup_types.emplace("slowdown", new SlowdownLevelup(&getNecessaryExpToLevelupSlowDown));
}

WaterTower::~WaterTower() = default;

void WaterTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    //if (difftime(time(nullptr), last_attack_time) < attack_cooldown) { return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(level->getRange());
    if (enemies.empty()) { return; }

    changeTarget(enemies);
    hitCurrentTarget(level->getDamage());
    current_target->reduceSpeed(level->getSpeedReduction(),
                                level->getSpeedReductionDuration());

    last_attack_time = time(nullptr);
}

WaterTower::WaterTower(WaterTower&& other) noexcept : Tower(std::move(other)) {}
