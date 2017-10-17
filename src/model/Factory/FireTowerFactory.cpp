//
// Created by facundo on 17/10/17.
//

#include "FireTowerFactory.h"
#include "../FireTower.h"

Tower *FireTowerFactory::create(int id, Vector position,
                                const YAML::Node &properties, Scenario& scenario) {
    return new FireTower(id, position, properties, scenario);
}
