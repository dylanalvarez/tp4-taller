//
// Created by facundo on 20/10/17.
//

#include "WaterTowerFactory.h"
#include "../Towers/WaterTower.h"

Tower *WaterTowerFactory::create(int id, Vector position,
                                 YAML::Node &properties, Scenario &scenario) {
    return new WaterTower(id, position, properties, scenario);
}
