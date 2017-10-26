//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_FIRETOWER_H
#define TOWERDEFENSE_FIRETOWER_H


#include "Tower.h"
#include "../Vector.h"

class FireTower : public Tower {
public:
    FireTower(int id, Vector p, YAML::Node& properties,
              Scenario& scneario);

    ~FireTower() override;

    void attack() override;

    void levelupRange() override;
    void levelupDamage() override;
    void levelupReachOfImpact() override;
    void levelupSlowdown() override;

    FireTower(const FireTower&) = delete;
    FireTower& operator=(const FireTower&) = delete;
    FireTower& operator=(FireTower&&) = delete;
    FireTower(FireTower&&) noexcept ;

private:
    int reach_level;
    unsigned int reach_upgrade;
    unsigned int reach_of_impact;
    unsigned int dmg_to_nearby_units;
    unsigned int dmg_to_nearby_units_upgrade;
    std::pair<int, float> reach_levelingup_function_values;
};


#endif //TOWERDEFENSE_FIRETOWER_H
