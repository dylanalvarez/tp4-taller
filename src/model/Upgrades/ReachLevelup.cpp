#include "ReachLevelup.h"
#include "../Towers/Tower.h"

ReachLevelup::ReachLevelup(Tower &tower) : LevelupType(tower) {}

void ReachLevelup::levelup() {
    tower.levelupReachOfImpact();
}
