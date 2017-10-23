//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_TOWERLEVEL_H
#define TOWERDEFENSE_TOWERLEVEL_H


#include "Range.h"

class TowerLevel {
public:
    TowerLevel(int level, unsigned int dmg, unsigned int dmg_to_flying_units,
               unsigned int dmg_to_nearby_units, int reach_of_impact,
               Range range, unsigned int speed_reduction,
               unsigned int speed_reduction_duration);

    // getters
    unsigned int getDamage() const;
    unsigned int getDamageToFlyingUnits() const;
    unsigned int getDamageToNearbyUnits() const;
    const Range& getRange() const;
    unsigned int getSpeedReduction() const;
    int getLevel() const;
    int getReachOfImpact() const;
    unsigned int getSpeedReductionDuration() const;

private:
    int level;
    unsigned int dmg;
    unsigned int dmg_to_flying_units;
    unsigned int dmg_to_nearby_units;
    Range range;
    unsigned int speed_reduction;
    unsigned int speed_reduction_duration;
    int reach_of_impact;
};


#endif //TOWERDEFENSE_TOWERLEVEL_H
