#include "DamageLevelup.h"
#include "../Towers/Tower.h"

DamageLevelup::DamageLevelup(Tower &tower) : LevelupType(tower) {}

void DamageLevelup::levelup() {
    tower.levelupDamage();
}
