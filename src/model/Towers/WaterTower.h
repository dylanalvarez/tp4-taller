//
// Created by facundo on 20/10/17.
//

#ifndef TOWERDEFENSE_WATERTOWER_H
#define TOWERDEFENSE_WATERTOWER_H


#include "Tower.h"

class WaterTower : public Tower {
public:
    WaterTower(int id, Vector position, YAML::Node& properties,
          Scenario& scenario);

    ~WaterTower() override;

    void attack() override;

    void levelupRange() override;
    void levelupDamage() override;
    void levelupReachOfImpact() override;
    void levelupSlowdown() override;

    Communication::Tower::Damage getDamage_() const override;
    Communication::Tower::Type getType() const override;
    Communication::Tower::EnemySlowdown getslowdown() const override;

    WaterTower(const WaterTower&) = delete;
    WaterTower& operator=(const WaterTower&) = delete;
    WaterTower& operator=(WaterTower&&) = delete;
    WaterTower(WaterTower&&) noexcept ;

private:
    int slowdown_level;
    unsigned int speed_reduction;
    unsigned int speed_reduction_duration;
    unsigned int speed_reduction_duration_upgrade;
    unsigned int speed_reduction_upgrade;
    std::pair<int, float> slowdown_levelingup_function_values;
};


#endif //TOWERDEFENSE_WATERTOWER_H
