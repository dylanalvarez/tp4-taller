//
// Created by facundo on 22/10/17.
//

#include "RangeLevelup.h"
#include "../Exceptions/TowerError.h"

RangeLevelup::RangeLevelup(float increment,
                           double (*getNecessaryExp)(int)) :
        LevelupType(getNecessaryExp),
        increment(increment) {}

TowerLevel* RangeLevelup::levelup(const TowerLevel& level, double actual_exp) {
    if (actual_exp < getNecessaryExp(level.getLevel())) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                                 std::to_string(actual_exp) +
                                 ", se necesitan" +
                                 std::to_string(getNecessaryExp(level.getLevel())));
    }

    Range new_Range(level.getRange().getCenter(), level.getRange().getRadius()
                                                  + increment);
    return new TowerLevel(level.getLevel() + 1,
                          level.getDamage(),
                          level.getDamageToFlyingUnits(),
                          level.getDamageToNearbyUnits(),
                          level.getReachOfImpact(),
                          new_Range,
                          level.getSpeedReduction(),
                          level.getSpeedReductionDuration());
}

double RangeLevelup::getExperienceNeededforLevel(int level) {
    return getNecessaryExp(level);
}
