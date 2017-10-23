//
// Created by facundo on 22/10/17.
//

#include "ReachLevelup.h"
#include "../Towers/Tower.h"

ReachLevelup::ReachLevelup(Tower &tower) : LevelupType(tower) {}

void ReachLevelup::levelup() {
    tower.levelupReachOfImpact();
}
