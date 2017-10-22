//
// Created by facundo on 21/10/17.
//

#ifndef TOWERDEFENSE_EARTHTOWER_H
#define TOWERDEFENSE_EARTHTOWER_H


#include "Tower.h"

class EarthTower : public Tower {
public:
    EarthTower(int id, Vector p, const YAML::Node& properties,
              Scenario& scneario);

    ~EarthTower() override;

    void attack() override;

    EarthTower(const EarthTower&) = delete;
    EarthTower& operator=(const EarthTower&) = delete;
    EarthTower& operator=(EarthTower&&) = delete;
    EarthTower(EarthTower&&) noexcept ;

};


#endif //TOWERDEFENSE_EARTHTOWER_H
