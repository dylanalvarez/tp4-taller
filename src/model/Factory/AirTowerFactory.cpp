#include "AirTowerFactory.h"
#include "../Towers/AirTower.h"

Tower *AirTowerFactory::create(int id, Vector position,
                               YAML::Node &properties,
                               Scenario &scenario) {
    return new AirTower(id, position, properties, scenario);
}
