//
// Created by facundo on 22/10/17.
//

#include "ReachLevelup.h"
#include "../Exceptions/TowerError.h"

ReachLevelup::ReachLevelup(int increment, double (*getNecessaryExp)(int)) :
        LevelupType(getNecessaryExp),
        increment(increment) {}

TowerLevel *ReachLevelup::levelup(const TowerLevel &level, double actual_exp) {
    if (actual_exp < getNecessaryExp(level.getLevel())) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(actual_exp) +
                         ", se necesitan" +
                         std::to_string(getNecessaryExp(level.getLevel())));
    }

    return new TowerLevel(level.getLevel() + 1,
                          level.getDamage(),
                          level.getDamageToFlyingUnits(),
                          level.getDamageToNearbyUnits(),
                          level.getReachOfImpact() + increment,
                          level.getRange(),
                          level.getSpeedReduction(),
                          level.getSpeedReductionDuration());
}

double ReachLevelup::getExperienceNeededforLevel(int level) {
    return getNecessaryExp(level);
}
