//
// Created by facundo on 21/10/17.
//

#include "EarthTowerFactory.h"
#include "../Towers/EarthTower.h"

Tower *EarthTowerFactory::create(int id, Vector position,
                                 const YAML::Node &properties,
                                 Scenario &scenario) {
    return new EarthTower(id, position, properties, scenario);
}
