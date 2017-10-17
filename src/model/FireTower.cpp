//
// Created by facundo on 10/10/17.
//

#include "FireTower.h"

FireTower::FireTower(int id, const Vector p, const YAML::Node& properties) :
        Tower() {
    this->position = p;
}

FireTower::~FireTower() = default;

void FireTower::attack() {

}
