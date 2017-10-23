//
// Created by facundo on 23/10/17.
//

#include "Fissure.h"

Fissure::Fissure(Scenario &scenario, unsigned int cooldown,
                 unsigned int duration) : scenario(scenario),
                                          cooldown(cooldown),
                                          duration(duration) {
    is_active = false;
    last_activation_time = 0;
}

void Fissure::applyEffect(const Vector &position) {
    this->position = position;
    is_active = true;
    last_activation_time = time(nullptr);
}

bool Fissure::canBeThrownBy(const std::string &element) {
    return element == "earth";
}

void Fissure::attack() {
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
        if (!enemy->canIFlight()) {
            // no afecta a los voladores
            enemy->reduceLife((unsigned)enemy->getHealthPoints());
        }
    }
}

void Fissure::applyEffect(Enemy &enemy) {}
