#include "FireTowerFactory.h"
#include "../Towers/FireTower.h"

Tower *FireTowerFactory::create(int id, Vector position,
                                YAML::Node &properties, Scenario &scenario) {
    return new FireTower(id, position, properties, scenario);
}
