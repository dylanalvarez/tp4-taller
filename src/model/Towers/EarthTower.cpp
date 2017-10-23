//
// Created by facundo on 21/10/17.
//

#include "EarthTower.h"
#include "../Scenario.h"
#include "../Upgrades/DamageLevelup.h"

static double getNecessaryExpToLevelupRange(int level) {
    return (500 * (pow(2,level)));
}

static double getNecessaryExpToLevelupDamage(int level) {
    return (100 * pow(1.5, level));
}

EarthTower::EarthTower(int id, Vector p, const YAML::Node &properties,
                       Scenario &scneario) :
        Tower(id, p, properties, scneario) {
    level = new TowerLevel(1, 20, 0, 0, 0, Range(position, 2), 0, 0);
    this->last_attack_time = 0;
    this->attack_cooldown = 5;
    this->current_target = nullptr;

    // levelea +1 rango
    levelup_types.emplace("range", new RangeLevelup(1,
                                                    &getNecessaryExpToLevelupRange));
    // levelea +10 ataque, 0 contra voladores, 0 contra cercanos
    levelup_types.emplace("damage", new DamageLevelup(10, 0, 0,
                                                      &getNecessaryExpToLevelupDamage));
}

EarthTower::~EarthTower() = default;

void EarthTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    //if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    //{ return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(level->getRange());
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

    hitCurrentTarget(level->getDamage());

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
