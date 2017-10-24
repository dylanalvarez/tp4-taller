//
// Created by facundo on 23/10/17.
//

#include "Fissure.h"

Fissure::Fissure(Scenario &scenario, unsigned int cooldown,
                 unsigned int duration) : Spell(scenario, cooldown), duration(duration) {}

void Fissure::applyEffect(const Vector &position) {
    activate(position);
}

bool Fissure::canBeThrownBy(const std::string &element) {
    return element == "earth";
}

void Fissure::attack() {
    checkIfIsActive(duration);

    if (!is_active) { return; }

    for (Enemy* enemy : scenario.getEnemiesInRange(Range(position, 0))) {
        if (!enemy->canIFlight()) {
            // no afecta a los voladores
            enemy->reduceLife((unsigned)enemy->getHealthPoints());
        }
    }
}

void Fissure::applyEffect(Enemy &enemy) {}

bool Fissure::isActive() const {
    return is_active;
}
