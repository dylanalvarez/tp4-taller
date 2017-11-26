#include "EarthTowerFactory.h"
#include "../Towers/EarthTower.h"

Tower *EarthTowerFactory::create(int id, Vector position,
                                 YAML::Node &properties,
                                 Scenario &scenario) {
    return new EarthTower(id, position, properties, scenario);
}
