//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_SLOWDOWNLEVELUP_H
#define TOWERDEFENSE_SLOWDOWNLEVELUP_H


#include "LevelupType.h"

class SlowdownLevelup: public LevelupType {
public:
    explicit SlowdownLevelup(Tower& tower);

    void levelup() override;
};


#endif //TOWERDEFENSE_SLOWDOWNLEVELUP_H
