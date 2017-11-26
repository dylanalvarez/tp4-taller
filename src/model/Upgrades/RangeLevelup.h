#ifndef TOWERDEFENSE_RANGELEVELUP_H
#define TOWERDEFENSE_RANGELEVELUP_H


#include "LevelupType.h"

class RangeLevelup : public LevelupType {
public:
    explicit RangeLevelup(Tower &tower);

    void levelup() override;
};


#endif //TOWERDEFENSE_RANGELEVELUP_H
