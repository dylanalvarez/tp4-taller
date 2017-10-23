//
// Created by facundo on 21/10/17.
//

#include "AirTower.h"
#include "../Scenario.h"
#include "../Upgrades/DamageLevelup.h"

static double getNecessaryExpToLevelupRange(int level){
    return (100 * (pow(2,level)));
}

static double getNecessaryExpToLevelupDamage(int level) {
    return (100 * pow(1.5, level));
}

AirTower::AirTower(int id, Vector p, const YAML::Node &properties,
                   Scenario &scneario) :
        Tower(id, p, properties, scneario) {
    level = new TowerLevel(1, 2, 10, 0, 0, Range(position, 5), 0, 0);

    this->last_attack_time = 0;
    this->attack_cooldown = 5;
    this->current_target = nullptr;

    // levelea +1 rango
    levelup_types.emplace("range", new RangeLevelup(1,
                                                    &getNecessaryExpToLevelupRange));
    // levelea +2 ataque, +10 contra voladores, 0 contra cercanos
    levelup_types.emplace("damage", new DamageLevelup(2, 10, 0,
                                                      &getNecessaryExpToLevelupDamage));
}

AirTower::~AirTower() = default;

void AirTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    //if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    //{ return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(level->getRange());
    if (enemies.empty()) { return; }

    changeTarget(enemies);

    // TODO sacar este if con clase Damage
    if (current_target->canIFlight()){
        hitCurrentTarget(level->getDamageToFlyingUnits());
    } else {
        hitCurrentTarget(level->getDamage());
    }

    // la torre de aire hace retroceder al enemigo
    current_target->moveBack();

    last_attack_time = time(nullptr);
}

AirTower::AirTower(AirTower&& other) noexcept : Tower(std::move(other)) {}
