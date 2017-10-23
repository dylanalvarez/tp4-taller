//
// Created by facundo on 23/10/17.
//

#include "Freezing.h"

Freezing::Freezing(Scenario &scenario, unsigned int cooldown,
                   unsigned int duration) :
        scenario(scenario), cooldown(cooldown), duration(duration) {
    is_active = false;
    last_activation_time = 0;
}

void Freezing::applyEffect(const Vector &position) {}

void Freezing::applyEffect(Enemy &enemy) {
    if (difftime(time(nullptr), last_activation_time) < cooldown) { return; }

    enemy.reduceSpeed(100, duration);
    last_activation_time = time(nullptr);
}

bool Freezing::canBeThrownBy(const std::string &element) {
    return element == "water";
}

void Freezing::attack() {}

bool Freezing::isActive() const {
    return is_active;
}
