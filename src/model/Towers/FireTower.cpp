//
// Created by facundo on 10/10/17.
//

#include <iostream>
#include "FireTower.h"
#include "../Scenario.h"
#include "../Exceptions/TowerError.h"
#include "../Upgrades/DamageLevelup.h"
#include "../Upgrades/ReachLevelup.h"

FireTower::FireTower(int id, const Vector position, YAML::Node& tower_properties,
                     Scenario& scenario) :
        Tower(id, position, scenario) {
    YAML::Node properties = tower_properties["fire_tower"];
    // basic properties
    dmg = properties["damage"].as<unsigned int>();
    dmg_to_nearby_units = properties["damage_to_nearby"].as<unsigned int>();
    range = Range(position, getRangeInTileSizes(properties["range"].as<float>()));
    attack_cooldown = properties["attack_rate"].as<unsigned int>();
    reach_of_impact = properties["reach"].as<unsigned int>();

    // upgrades properties
    dmg_upgrade = properties["damage_upgrade"].as<unsigned int>();
    dmg_to_nearby_units_upgrade =
            properties["damage_to_nearby_upgrade"].as<unsigned int>();
    range_upgrade = properties["range_upgrade"].as<unsigned int>();
    reach_upgrade = properties["reach_upgrade"].as<unsigned int>();

    // experience properties (base y exponente)
    range_levelingup_function_values.first =
            properties["range_base"].as<int>();
    range_levelingup_function_values.second =
            properties["range_exponent"].as<float>();
    dmg_levelingup_function_values.first =
            properties["dmg_base"].as<int>();
    dmg_levelingup_function_values.second =
            properties["dmg_exponent"].as<float>();
    reach_levelingup_function_values.first =
            properties["reach_base"].as<int>();
    reach_levelingup_function_values.second =
            properties["reach_exponent"].as<float>();

    range_level = 1;
    dmg_level = 1;
    reach_level = 1;

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
    if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    { is_attacking = false; return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(range);
    if (enemies.empty()) { return; }

    changeTarget(enemies);
    hitCurrentTarget(dmg);

    // daño a los enemigos cercanos
    for (unsigned int i = 1; i < enemies.size(); i++) {
        if ((enemies[i]->getCurrentPosition() -
             enemies[0]->getCurrentPosition()).getNorm() <=
                reach_of_impact) {
            // si estan al alcance del impacto
            experience += enemies[i]->reduceLife(dmg_to_nearby_units);
        }
    }

    last_attack_time = time(nullptr);
    is_attacking = true;
}

FireTower::FireTower(FireTower&& other) noexcept : Tower(std::move(other)) {}

void FireTower::levelupRange() {
    double neccessary_exp =
            range_levelingup_function_values.first *
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

void FireTower::levelupDamage() {
    double neccessary_exp =
            dmg_levelingup_function_values.first *
                    (pow(dmg_levelingup_function_values.second,dmg_level));
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));
    }
    dmg += dmg_upgrade;
    dmg_to_nearby_units += dmg_to_nearby_units_upgrade;
    experience -= neccessary_exp;
    dmg_level++;
}

void FireTower::levelupReachOfImpact() {
    double neccessary_exp =
            reach_levelingup_function_values.first *
                    (pow(reach_levelingup_function_values.second,reach_level));
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));

    }
    reach_of_impact += reach_upgrade;
    experience -= neccessary_exp;
    reach_level++;
}

void FireTower::levelupSlowdown() {}

Communication::Tower::Damage FireTower::getDamage_() const {
    return Communication::Tower::Damage(dmg, dmg, dmg_to_nearby_units);
}

Communication::Tower::Type FireTower::getType() const {
    return Communication::Tower::Type::fire;
}

int FireTower::getExplosionRange() const {
    return reach_of_impact;
}

int FireTower::getSlowDownLevel() const {
    return 0;
}

int FireTower::getReachLevel() const {
    return reach_level;
}
