//
// Created by facundo on 21/10/17.
//

#ifndef TOWERDEFENSE_AIRTOWER_H
#define TOWERDEFENSE_AIRTOWER_H


#include "Tower.h"

class AirTower : public Tower {
public:
    AirTower(int id, Vector p, YAML::Node& properties,
               Scenario& scneario);

    ~AirTower() override;

    void attack() override;

    void levelupRange() override;
    void levelupDamage() override;
    void levelupReachOfImpact() override;
    void levelupSlowdown() override;

    AirTower(const AirTower&) = delete;
    AirTower& operator=(const AirTower&) = delete;
    AirTower& operator=(AirTower&&) = delete;
    AirTower(AirTower&&) noexcept ;

private:
    unsigned int dmg_to_flying_units;
    unsigned int dmg_to_flying_units_upgrade;
};


#endif //TOWERDEFENSE_AIRTOWER_H
