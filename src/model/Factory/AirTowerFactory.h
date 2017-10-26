//
// Created by facundo on 21/10/17.
//

#ifndef TOWERDEFENSE_AIRTOWERFACTORY_H
#define TOWERDEFENSE_AIRTOWERFACTORY_H


#include "TowerFactory.h"

class AirTowerFactory : public TowerFactory {
    Tower* create(int id, Vector position, YAML::Node& properties,
                  Scenario& scenario) override;
};


#endif //TOWERDEFENSE_AIRTOWERFACTORY_H
