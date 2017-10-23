//
// Created by facundo on 22/10/17.
//

#include "DamageLevelup.h"
#include "../Towers/Tower.h"

DamageLevelup::DamageLevelup(Tower &tower) : LevelupType(tower) {}

void DamageLevelup::levelup() {
    tower.levelupDamage();
}
