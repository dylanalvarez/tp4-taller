//
// Created by facundo on 22/10/17.
//

#include "SlowdownLevelup.h"
#include "../Towers/Tower.h"

SlowdownLevelup::SlowdownLevelup(Tower &tower) : LevelupType(tower) {}

void SlowdownLevelup::levelup() {
    tower.levelupSlowdown();
}
