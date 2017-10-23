//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_RANGELEVELUP_H
#define TOWERDEFENSE_RANGELEVELUP_H


#include "LevelupType.h"
#include "../TowerLevel.h"

class RangeLevelup : public LevelupType {
public:
    // recibe un valor de incremento y un puntero a funcion que recibe
    // un entero y retorna un float (calcula la exp necesaria)
    RangeLevelup(float increment, double (*)(int));

    TowerLevel* levelup(const TowerLevel& level, double actual_exp) override;

    double getExperienceNeededforLevel(int level) override;

private:
    float increment;
};


#endif //TOWERDEFENSE_RANGELEVELUP_H
