//
// Created by facundo on 23/10/17.
//

#include "Blizzard.h"

Blizzard::Blizzard(Scenario& scenario, unsigned int cooldown,
                   unsigned int duration, unsigned int dmg,
                   unsigned int speed_reduction,
                   unsigned int speed_reduction_duration) :
        scenario(scenario),
        cooldown(cooldown),
        dmg(dmg),
        duration(duration),
        speed_reduction(speed_reduction),
        speed_reduction_duration(speed_reduction_duration) {
    is_active = false;
    last_activation_time = 0;
}

void Blizzard::applyEffect(const Vector &position) {
    if (difftime(time(nullptr), last_activation_time) < cooldown) { return; }

    is_active = true;
    this->position = position;
    last_activation_time = time(nullptr);
}

void Blizzard::applyEffect(Enemy &enemy) {}

bool Blizzard::canBeThrownBy(const std::string &element) {
    return element == "water";
}

void Blizzard::attack() {
    if (difftime(time(nullptr), last_activation_time) >= duration) {
        is_active = false;
    }

    if (!is_active || (!is_active &&
                       difftime(time(nullptr), last_activation_time) < cooldown)) {
        // si no esta activo salir.
        // si se activo y se termino su duracion y no paso su cooldown salir
        return;
    }

    for (Enemy* enemy : scenario.getEnemiesInRange(Range(position, 0))) {
        enemy->reduceLife(dmg);
        enemy->reduceSpeed(speed_reduction, speed_reduction_duration);
    }
}

bool Blizzard::isActive() const {
    return is_active;
}
