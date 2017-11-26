//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_RANGELEVELUP_H
#define TOWERDEFENSE_RANGELEVELUP_H


#include "LevelupType.h"

class RangeLevelup : public LevelupType {
public:
    explicit RangeLevelup(Tower &tower);

    void levelup() override;
};


#endif //TOWERDEFENSE_RANGELEVELUP_H
