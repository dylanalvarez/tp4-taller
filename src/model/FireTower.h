//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_FIRETOWER_H
#define TOWERDEFENSE_FIRETOWER_H


#include "Tower.h"
#include "Position.h"

class FireTower : public Tower {
public:
    FireTower(Position p, unsigned int initial_damage,
              unsigned int speed_reduction);

    ~FireTower() override;

    void attack() override;
};


#endif //TOWERDEFENSE_FIRETOWER_H
