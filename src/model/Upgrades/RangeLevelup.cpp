#include "RangeLevelup.h"
#include "../Towers/Tower.h"

RangeLevelup::RangeLevelup(Tower &tower) : LevelupType(tower) {}

void RangeLevelup::levelup() {
    tower.levelupRange();
}
