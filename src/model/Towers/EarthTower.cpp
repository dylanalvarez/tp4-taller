//
// Created by facundo on 21/10/17.
//

#include "EarthTower.h"
#include "../Scenario.h"
#include "../Exceptions/TowerError.h"
#include "../Upgrades/DamageLevelup.h"

EarthTower::EarthTower(int id, Vector p, YAML::Node &tower_properties,
                       Scenario &scneario) :
        Tower(id, p, scneario) {
    YAML::Node properties = tower_properties["earth_tower"];
    // basic properties
    dmg = properties["damage"].as<unsigned int>();
    range = Range(position, getRangeInTileSizes(properties["range"].as<int>()));
    attack_cooldown = properties["attack_rate"].as<unsigned int>();

    // upgrades properties
    dmg_upgrade = properties["damage_upgrade"].as<unsigned int>();
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

EarthTower::~EarthTower() = default;

void EarthTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    if (difftime(time(nullptr), last_attack_time) < attack_cooldown)
    { return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(range);
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

    hitCurrentTarget(dmg);

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

void EarthTower::levelupDamage() {
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
    dmg_level++;
    experience -= neccessary_exp;
}

void EarthTower::levelupRange() {
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

void EarthTower::levelupReachOfImpact() {}

void EarthTower::levelupSlowdown() {}

Communication::Tower::Damage EarthTower::getDamage_() const {
    return Communication::Tower::Damage(dmg, 0, 0);
}

Communication::Tower::Type EarthTower::getType() const {
    return Communication::Tower::Type::earth;
}

int EarthTower::getSlowDownLevel() const {
    return 0;
}

int EarthTower::getReachLevel() const {
    return 0;
}
