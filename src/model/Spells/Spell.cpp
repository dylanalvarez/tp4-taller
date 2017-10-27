//
// Created by facundo on 24/10/17.
//

#include "Spell.h"

Spell::Spell(Scenario &scenario, unsigned int cooldown) :
        scenario(scenario), cooldown(cooldown) {
    is_active = false;
    last_activation_time = 0;
    is_on_cooldown = false;
}


void Spell::activate(const Vector &position) {
    if (isOnCooldown()) { return; }

    is_active = true;
    this->position = position;
    last_activation_time = time(nullptr);
    target_id = -1;
}

void Spell::checkIfIsActive(unsigned int duration) {
    if (difftime(time(nullptr), last_activation_time) >= duration) {
        is_active = false;
    }
}

bool Spell::isOnCooldown() {
    // check cooldown
    is_on_cooldown = difftime(time(nullptr), last_activation_time) < cooldown;

    return is_on_cooldown;
}

const Vector &Spell::getPosition() const {
    return position;
}

const int Spell::getTargetID() const {
    return target_id;
}
