//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_FIRETOWER_H
#define TOWERDEFENSE_FIRETOWER_H


#include "Tower.h"
#include "Vector.h"

class FireTower : public Tower {
public:
    FireTower(int id, const Vector& p, YAML::Node properties);

    ~FireTower() override;

    void attack() override;
};


#endif //TOWERDEFENSE_FIRETOWER_H
