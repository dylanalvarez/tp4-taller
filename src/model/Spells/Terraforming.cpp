//
// Created by facundo on 23/10/17.
//

#include "Terraforming.h"

Terraforming::Terraforming(Scenario &scenario, unsigned int cooldown) :
                            scenario(scenario), cooldown(cooldown) {
    is_active = false;
}

void Terraforming::applyEffect(const Vector &position) {
    if (difftime(time(nullptr), last_activation_time) < cooldown) {
        return;
    }

    scenario.addFirmGround(position);
    last_activation_time = time(nullptr);
}

bool Terraforming::canBeThrownBy(const std::string &element) {
    return element == "earth";
}

void Terraforming::attack() {}
