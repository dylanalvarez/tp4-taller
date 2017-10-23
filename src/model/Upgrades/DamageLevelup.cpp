//
// Created by facundo on 22/10/17.
//

#include "DamageLevelup.h"
#include "../Exceptions/TowerError.h"

DamageLevelup::DamageLevelup(unsigned int dmg, unsigned int dmg_to_flying_units,
                             unsigned int dmg_to_nearby_units,
                             double(*getNecessaryExp)(int)) :
        LevelupType(getNecessaryExp),
        dmg(dmg),
        dmg_to_nearby_units(dmg_to_nearby_units),
        dmg_to_flying_units(dmg_to_flying_units) {}

TowerLevel *DamageLevelup::levelup(const TowerLevel &level, double actual_exp) {
    if (actual_exp < getNecessaryExp(level.getLevel())) {
        throw TowerError("Error: no se puede subir de nivel con los puntos" +
                         std::to_string(actual_exp) +
                         ", se necesitan" +
                         std::to_string(getNecessaryExp(level.getLevel())));
    }

    return new TowerLevel(level.getLevel() + 1,
                          level.getDamage() + dmg,
                          level.getDamageToFlyingUnits() + dmg_to_flying_units,
                          level.getDamageToNearbyUnits() + dmg_to_nearby_units,
                          level.getReachOfImpact(),
                          level.getRange(),
                          level.getSpeedReduction(),
                          level.getSpeedReductionDuration());
}

double DamageLevelup::getExperienceNeededforLevel(int level) {
    return getNecessaryExp(level);
}
