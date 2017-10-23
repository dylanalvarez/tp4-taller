//
// Created by facundo on 22/10/17.
//

#include "TowerLevel.h"

TowerLevel::TowerLevel(int level, unsigned int dmg, unsigned int dmg_to_flying_units,
                       unsigned int dmg_to_nearby_units, int reach_of_impact,
                       Range range, unsigned int speed_reduction,
                       unsigned int speed_reduction_duration) :
        level(level),
        dmg(dmg),
        dmg_to_flying_units(dmg_to_flying_units),
        dmg_to_nearby_units(dmg_to_nearby_units),
        range(range),
        speed_reduction(speed_reduction),
        reach_of_impact(reach_of_impact),
        speed_reduction_duration(speed_reduction_duration) {}

unsigned int TowerLevel::getDamage() const {
    return dmg;
}

unsigned int TowerLevel::getDamageToFlyingUnits() const {
    return dmg_to_flying_units;
}

const Range &TowerLevel::getRange() const {
    return range;
}

unsigned int TowerLevel::getSpeedReduction() const {
    return speed_reduction;
}

unsigned int TowerLevel::getDamageToNearbyUnits() const {
    return dmg_to_nearby_units;
}

int TowerLevel::getLevel() const {
    return level;
}

int TowerLevel::getReachOfImpact() const {
    return reach_of_impact;
}

unsigned int TowerLevel::getSpeedReductionDuration() const {
    return speed_reduction_duration;
}
