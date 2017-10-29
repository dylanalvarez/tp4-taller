//
// Created by facundo on 17/10/17.
//

#ifndef TOWERDEFENSE_TOWERFACTORY_H
#define TOWERDEFENSE_TOWERFACTORY_H


#include "../Towers/Tower.h"
#include "../Scenario.h"

class TowerFactory {
public:
    virtual Tower* create(int id, Vector p, YAML::Node& properties,
                          Scenario& scenario) = 0;
    virtual ~TowerFactory() = default;
};

#endif //TOWERDEFENSE_TOWERFACTORY_H
