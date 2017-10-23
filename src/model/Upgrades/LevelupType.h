//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_LEVELUPTYPE_H
#define TOWERDEFENSE_LEVELUPTYPE_H


#include "../TowerLevel.h"

class LevelupType {
public:
    explicit LevelupType(double (*)(int));

    virtual TowerLevel* levelup(const TowerLevel& level, double actual_exp) = 0;

    virtual double getExperienceNeededforLevel(int) = 0;

protected:
    double(*getNecessaryExp)(int);
};


#endif //TOWERDEFENSE_LEVELUPTYPE_H
