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

    WaterTower(const WaterTower&) = delete;
    WaterTower& operator=(const WaterTower&) = delete;
    WaterTower& operator=(WaterTower&&) = delete;
    WaterTower(WaterTower&&) noexcept ;

private:
    int slowdown_level;
    unsigned int speed_reduction;
    unsigned int speed_reduction_duration;
};


#endif //TOWERDEFENSE_WATERTOWER_H
