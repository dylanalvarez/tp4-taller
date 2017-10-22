//
// Created by facundo on 20/10/17.
//

#ifndef TOWERDEFENSE_WATERTOWERFACTORY_H
#define TOWERDEFENSE_WATERTOWERFACTORY_H


#include "TowerFactory.h"

class WaterTowerFactory : public TowerFactory {
public:
    Tower* create(int id, Vector position, const YAML::Node& properties,
                  Scenario& scenario) override;
};


#endif //TOWERDEFENSE_WATERTOWERFACTORY_H
