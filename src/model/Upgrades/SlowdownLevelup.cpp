//
// Created by facundo on 22/10/17.
//

#include <netinet/in.h>
#include "SlowdownLevelup.h"
#include "../TowerLevel.h"
#include "../Exceptions/TowerError.h"

SlowdownLevelup::SlowdownLevelup(double (*)(int)) :
        LevelupType(getNecessaryExp) {}

TowerLevel *SlowdownLevelup::levelup(const TowerLevel &level, double actual_exp) {
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
                          level.getReachOfImpact(),
                          level.getRange(),
                          level.getSpeedReduction() + 25,
                          level.getSpeedReductionDuration());
}

double SlowdownLevelup::getExperienceNeededforLevel(int level) {
    return getNecessaryExp(level);
}
