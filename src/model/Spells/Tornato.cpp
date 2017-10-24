//
// Created by facundo on 24/10/17.
//

#include "Tornato.h"

Tornato::Tornato(Scenario &scenario, unsigned int cooldown,
                 unsigned int min_dmg, unsigned int max_dmg, unsigned int duration) :
                                            scenario(scenario),
                                            cooldown(cooldown),
                                            min_dmg(min_dmg),
                                            max_dmg(max_dmg),
                                            duration(duration) {
    is_active = false;
    last_activation_time = 0;
}

void Tornato::applyEffect(const Vector &position) {
    if (difftime(time(nullptr), last_activation_time) < cooldown) { return; }

    is_active = true;
    this->position = position;
    last_activation_time = time(nullptr);
}

void Tornato::applyEffect(Enemy &enemy) {}

bool Tornato::canBeThrownBy(const std::string &element) {
    return element == "air";
}

void Tornato::attack() {
    if (difftime(time(nullptr), last_activation_time) >= duration) {
        is_active = false;
    }

    if (!is_active || (!is_active &&
                       difftime(time(nullptr), last_activation_time) < cooldown)) {
        // si no esta activo salir.
        // si se activo y se termino su duracion y no paso su cooldown salir
        return;
    }

    // sera usada para obtener un "seed" para el engine generador de numeros
    std::random_device rd;
    // engine seeded with rd
    std::mt19937 gen(rd());
    // distribucion uniforme
    std::uniform_int_distribution<> distribution(min_dmg, max_dmg);

    for (Enemy* enemy : scenario.getEnemiesInRange(Range(position, 0))) {
        enemy->reduceLife((unsigned)distribution(gen));
    }
}

bool Tornato::isActive() const {
    return is_active;
}
