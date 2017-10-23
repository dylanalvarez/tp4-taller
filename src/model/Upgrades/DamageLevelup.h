//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_DAMAGELEVELUP_H
#define TOWERDEFENSE_DAMAGELEVELUP_H


#include "LevelupType.h"

class DamageLevelup : public LevelupType {
public:
    // recibe el incremento en el ataque y un puntero a una funcion
    // que calcula la experiencia necesaria
    DamageLevelup(unsigned int dmg, unsigned int dmg_to_flying_units,
                  unsigned int dmg_to_nearby_units, double (*)(int));

    TowerLevel* levelup(const TowerLevel& level, double actual_exp) override;

    double getExperienceNeededforLevel(int level) override;

private:
    unsigned int dmg;
    unsigned int dmg_to_flying_units;
    unsigned int dmg_to_nearby_units;
};


#endif //TOWERDEFENSE_DAMAGELEVELUP_H
