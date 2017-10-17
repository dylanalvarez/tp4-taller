//
// Created by facundo on 10/10/17.
//

#include "Tower.h"

Tower::Tower(int id, Vector position, const YAML::Node& properties,
             Scenario& scenario) : experience(0), id(id),
                                   properties(properties),
                                   scenario(scenario) {}

Tower::~Tower() = default;

unsigned int Tower::getExperience() const {
    return experience;
}

const Vector &Tower::getPosition() const {
    return position;
}
