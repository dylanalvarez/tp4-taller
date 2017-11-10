//
// Created by facundo on 20/10/17.
//

#include "WaterTower.h"
#include "../Scenario.h"
#include "../Exceptions/TowerError.h"
#include "../Upgrades/DamageLevelup.h"
#include "../Upgrades/SlowdownLevelup.h"

WaterTower::WaterTower(int id, Vector position,
                       YAML::Node &tower_properties, Scenario &scenario) :
        Tower(id, position, scenario) {
    YAML::Node properties = tower_properties["water_tower"];
    // basic properties
    dmg = properties["damage"].as<unsigned int>();
    speed_reduction = properties["speed_reduction"].as<unsigned int>();
    range = Range(position, getRangeInTileSizes(properties["range"].as<int>()));
    attack_cooldown = properties["attack_rate"].as<unsigned int>();
    speed_reduction_duration =
            properties["speed_reduction_duration"].as<unsigned int>();

    // upgrades properties
    dmg_upgrade = properties["damage_upgrade"].as<unsigned int>();
    speed_reduction_upgrade =
            properties["speed_reduction_upgrade"].as<unsigned int>();
    speed_reduction_duration_upgrade =
            properties["speed_reduction_duration_upgrade"].as<unsigned int>();
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
    slowdown_levelingup_function_values.first =
            properties["speed_reduction_base"].as<int>();
    slowdown_levelingup_function_values.second =
            properties["speed_reduction_exponent"].as<float>();

    range_level = 1;
    dmg_level = 1;
    slowdown_level = 1;

    last_attack_time = 0;
    current_target = nullptr;
    experience = 0;

    levelup_types.emplace("range", new RangeLevelup(*this));
    levelup_types.emplace("damage", new DamageLevelup(*this));
    levelup_types.emplace("slowdown", new SlowdownLevelup(*this));
}

WaterTower::~WaterTower() = default;

void WaterTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    { is_attacking = false; return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(range);
    if (enemies.empty()) { return; }

    changeTarget(enemies);
    hitCurrentTarget(dmg);
    current_target->reduceSpeed(speed_reduction, speed_reduction_duration);

    last_attack_time = time(nullptr);
    is_attacking = true;
}

WaterTower::WaterTower(WaterTower&& other) noexcept : Tower(std::move(other)) {}

void WaterTower::levelupRange() {
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

void WaterTower::levelupDamage() {
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
    experience -= neccessary_exp;
    dmg_level++;
}

void WaterTower::levelupSlowdown() {
    double neccessary_exp =
            slowdown_levelingup_function_values.first *
                    (pow(slowdown_levelingup_function_values.second,slowdown_level));
    if (experience < neccessary_exp) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(experience) +
                         ", se necesitan" +
                         std::to_string(neccessary_exp));
    }

    if (speed_reduction >= 100) {
        speed_reduction_duration += speed_reduction_duration_upgrade;
    } else {
        speed_reduction += speed_reduction_upgrade;
    }
    experience -= neccessary_exp;
    slowdown_level++;
}

void WaterTower::levelupReachOfImpact() {}

Communication::Tower::Damage WaterTower::getDamage_() const {
    return Communication::Tower::Damage(dmg, dmg, 0);
}

Communication::Tower::Type WaterTower::getType() const {
    return Communication::Tower::Type::water;
}

Communication::Tower::EnemySlowdown WaterTower::getslowdown() const {
    return Communication::Tower::EnemySlowdown
            {(int)speed_reduction, (int)speed_reduction_duration};
}

int WaterTower::getSlowDownLevel() const {
    return slowdown_level;
}

int WaterTower::getReachLevel() const {
    return 0;
}
