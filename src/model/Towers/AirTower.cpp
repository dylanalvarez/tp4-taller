//
// Created by facundo on 21/10/17.
//

#include "AirTower.h"
#include "../Scenario.h"
#include "../Exceptions/TowerError.h"
#include "../Upgrades/DamageLevelup.h"

AirTower::AirTower(int id, Vector p, YAML::Node &tower_properties,
                   Scenario &scneario) :
        Tower(id, p, scneario) {

    YAML::Node properties = tower_properties["air_tower"];
    // basic properties
    dmg = properties["damage"].as<unsigned int>();
    dmg_to_flying_units = properties["damage_to_flying"].as<unsigned int>();
    range = Range(position, properties["range"].as<int>());
    attack_cooldown = properties["attack_rate"].as<unsigned int>();

    // upgrades properties
    dmg_upgrade = properties["damage_upgrade"].as<unsigned int>();
    dmg_to_flying_units_upgrade =
            properties["damage_to_flying_upgrade"].as<unsigned int>();
    range_upgrade = properties["range_upgrade"].as<unsigned int>();

    // experience properties (base y exponente)
    range_levelingup_function_values.first =
            properties["range_base"].as<int>();
    range_levelingup_function_values.second =
            properties["range_exponent"].as<float>();
    dmg_levelingup_function_values.first =
            properties["dmg_base"].as<int>();
    dmg_levelingup_function_values.second =
            properties["dmg_exponent"].as<float>();

    range_level = 1;
    dmg_level = 1;
    last_attack_time = 0;
    current_target = nullptr;
    experience = 0;

    levelup_types.emplace("range", new RangeLevelup(*this));
    levelup_types.emplace("damage", new DamageLevelup(*this));
}

AirTower::~AirTower() = default;

void AirTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    { return; }

    std::vector<Enemy*> enemies = std::move(scenario.getEnemiesInRange(range));
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
    double neccessary_exp = range_levelingup_function_values.first *
            (pow(range_levelingup_function_values.second,range_level));
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));
    }

    range = Range(position, range.getRadius() + range_upgrade);
    experience -= neccessary_exp;
    range_level++;
}

void AirTower::levelupDamage() {
    double neccessary_exp = dmg_levelingup_function_values.first *
                    pow(dmg_levelingup_function_values.second, dmg_level);
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));
    }

    dmg += dmg_upgrade;
    dmg_to_flying_units += dmg_to_flying_units_upgrade;
    experience -= neccessary_exp;
    dmg_level++;
}

void AirTower::levelupReachOfImpact() {}

void AirTower::levelupSlowdown() {}
