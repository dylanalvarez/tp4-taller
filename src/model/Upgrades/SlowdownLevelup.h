//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_SLOWDOWNLEVELUP_H
#define TOWERDEFENSE_SLOWDOWNLEVELUP_H


#include "LevelupType.h"

class SlowdownLevelup: public LevelupType {
public:
    // recibe un valor de incremento y un puntero a funcion que recibe
    // un entero y retorna un float (calcula la exp necesaria)
    SlowdownLevelup(double (*)(int));

    TowerLevel* levelup(const TowerLevel& level, double actual_exp) override;

    double getExperienceNeededforLevel(int level) override;
};


#endif //TOWERDEFENSE_SLOWDOWNLEVELUP_H
