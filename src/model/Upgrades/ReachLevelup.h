//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_REACHLEVELUP_H
#define TOWERDEFENSE_REACHLEVELUP_H


#include "LevelupType.h"

class ReachLevelup : public LevelupType {
public:
    explicit ReachLevelup(Tower& tower);

    void levelup() override;
};

#endif //TOWERDEFENSE_REACHLEVELUP_H
