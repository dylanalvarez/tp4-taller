//
// Created by facundo on 21/10/17.
//

#include "AirTowerFactory.h"
#include "../Towers/AirTower.h"

Tower *AirTowerFactory::create(int id, Vector position,
                               YAML::Node &properties,
                               Scenario &scenario) {
    return new AirTower(id, position, properties, scenario);
}
