//
// Created by facundo on 20/10/17.
//

#ifndef TOWERDEFENSE_WATERTOWER_H
#define TOWERDEFENSE_WATERTOWER_H


#include "Tower.h"

class WaterTower : public Tower {
public:
    WaterTower(int id, Vector position, const YAML::Node& properties,
          Scenario& scenario);

    ~WaterTower() override;

    void attack() override;

    WaterTower(const WaterTower&) = delete;
    WaterTower& operator=(const WaterTower&) = delete;
    WaterTower& operator=(WaterTower&&) = delete;
    WaterTower(WaterTower&&) noexcept ;

private:
    unsigned int speed_reduction;
    unsigned int speed_reduction_time;
};


#endif //TOWERDEFENSE_WATERTOWER_H
