//
// Created by facundo on 23/10/17.
//

#include "Terraforming.h"

Terraforming::Terraforming(Scenario &scenario, unsigned int cooldown) :
        Spell(scenario, cooldown) {}

void Terraforming::applyEffect(const Vector &position) {
    if (isOnCooldown()) { return; }

    scenario.addFirmGround(position);
    last_activation_time = time(nullptr);
}

bool Terraforming::canBeThrownBy(const std::string &element) {
    return element == "earth";
}

void Terraforming::attack() {}

void Terraforming::applyEffect(Enemy &enemy) {}

bool Terraforming::isActive() const {
    return is_active;
}
