//
// Created by facundo on 24/10/17.
//

#include "Tornato.h"

Tornato::Tornato(Scenario &scenario, unsigned int cooldown,
                 unsigned int min_dmg, unsigned int max_dmg, unsigned int duration) :
Spell(scenario, cooldown),
min_dmg(min_dmg),
max_dmg(max_dmg),
duration(duration) {}

void Tornato::applyEffect(const Vector &position) {
   activate(position);
}

void Tornato::applyEffect(Enemy &enemy) {}

bool Tornato::canBeThrownBy(const std::string &element) {
    return element == "air";
}

void Tornato::attack() {
    checkIfIsActive(duration);

    if (!is_active) { return; }

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
