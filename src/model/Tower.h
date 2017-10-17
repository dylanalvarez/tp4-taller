//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_TOWER_H
#define TOWERDEFENSE_TOWER_H


#include "Vector.h"

class Tower {
public:
    Tower();
    virtual ~Tower();

    virtual void attack() = 0;

    unsigned int getExperience() const;

    const Vector& getPosition() const;

protected:
    unsigned int experience;
    Vector position;
};


#endif //TOWERDEFENSE_TOWER_H
