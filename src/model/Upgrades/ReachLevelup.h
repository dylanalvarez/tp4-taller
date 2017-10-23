//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_REACHLEVELUP_H
#define TOWERDEFENSE_REACHLEVELUP_H


#include "LevelupType.h"

class ReachLevelup : public LevelupType {
public:
    // recibe un valor de incremento y un puntero a funcion que recibe
    // un entero y retorna un float (calcula la exp necesaria)
    ReachLevelup(int increment, double (*)(int));

    TowerLevel* levelup(const TowerLevel& level, double actual_exp) override;

    double getExperienceNeededforLevel(int level) override;

private:
    int increment;
};

#endif //TOWERDEFENSE_REACHLEVELUP_H
