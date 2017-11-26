#ifndef TOWERDEFENSE_WATERTOWERFACTORY_H
#define TOWERDEFENSE_WATERTOWERFACTORY_H


#include "TowerFactory.h"

class WaterTowerFactory : public TowerFactory {
public:
    Tower *create(int id, Vector position, YAML::Node &properties,
                  Scenario &scenario) override;
};


#endif //TOWERDEFENSE_WATERTOWERFACTORY_H
