//
// Created by facundo on 21/10/17.
//

#include "AirTower.h"
#include "../Scenario.h"
#include "../Exceptions/TowerError.h"
#include "../Upgrades/DamageLevelup.h"

AirTower::AirTower(int id, Vector p, const YAML::Node &properties,
                   Scenario &scneario) :
        Tower(id, p, properties, scneario) {
    range_level = 1;
    dmg_level = 1;
    this->dmg = 2;
    this->dmg_to_flying_units = 10;
    this->last_attack_time = 0;
    this->attack_cooldown = 5;
    this->current_target = nullptr;
    this->range = Range(position, 5);
    experience = 0;

    levelup_types.emplace("range", new RangeLevelup(*this));
    levelup_types.emplace("damage", new DamageLevelup(*this));
}

AirTower::~AirTower() = default;

void AirTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    //if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    //{ return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(range);
    if (enemies.empty()) { return; }

    changeTarget(enemies);

    // TODO sacar este if con clase Damage
    if (current_target->canIFlight()){
        hitCurrentTarget(dmg_to_flying_units);
    } else {
        hitCurrentTarget(dmg);
    }

    // la torre de aire hace retroceder al enemigo
    current_target->moveBack();

    last_attack_time = time(nullptr);
}

AirTower::AirTower(AirTower&& other) noexcept : Tower(std::move(other)) {}

void AirTower::levelupRange() {
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

void AirTower::levelupDamage() {
    double neccessary_exp = 100 * pow(1.5, dmg_level);
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));
    }

    this->dmg += 2;
    this->dmg_to_flying_units += 10;
    experience -= neccessary_exp;
    dmg_level++;
}

void AirTower::levelupReachOfImpact() {}

void AirTower::levelupSlowdown() {}
