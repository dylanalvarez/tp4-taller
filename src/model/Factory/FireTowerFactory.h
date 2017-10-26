//
// Created by facundo on 17/10/17.
//

#ifndef TOWERDEFENSE_FIRETOWERFACTORY_H
#define TOWERDEFENSE_FIRETOWERFACTORY_H


#include "TowerFactory.h"

class FireTowerFactory : public TowerFactory {
public:
    Tower* create(int id, Vector position, YAML::Node& properties,
                  Scenario& scenario) override;
};


#endif //TOWERDEFENSE_FIRETOWERFACTORY_H
