//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_DAMAGELEVELUP_H
#define TOWERDEFENSE_DAMAGELEVELUP_H


#include "LevelupType.h"

class DamageLevelup : public LevelupType {
public:
    explicit DamageLevelup(Tower &tower);

    void levelup() override;
};


#endif //TOWERDEFENSE_DAMAGELEVELUP_H
