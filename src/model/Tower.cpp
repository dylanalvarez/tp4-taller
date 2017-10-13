//
// Created by facundo on 10/10/17.
//

#include "Tower.h"

Tower::Tower() : experience(0) {}

Tower::~Tower() = default;

unsigned int Tower::getExperience() const {
    return experience;
}
