//
// Created by facundo on 21/10/17.
//

#ifndef TOWERDEFENSE_EARTHTOWERFACTORY_H
#define TOWERDEFENSE_EARTHTOWERFACTORY_H


#include "TowerFactory.h"

class EarthTowerFactory : public TowerFactory {
    Tower* create(int id, Vector position, YAML::Node& properties,
                  Scenario& scenario) override;
};


#endif //TOWERDEFENSE_EARTHTOWERFACTORY_H
