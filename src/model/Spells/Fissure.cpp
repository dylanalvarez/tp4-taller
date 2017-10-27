//
// Created by facundo on 23/10/17.
//

#include "Fissure.h"
#include "../Exceptions/MatchError.h"

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

    for (Enemy* enemy : scenario.getEnemiesInRange(Range(position, tile_size))) {
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

Communication::PositionalPower::Type Fissure::getPositionalType() const {
    return Communication::PositionalPower::Type::fissure;
}

Communication::TargetPower::Type Fissure::getTargetType() const {
    throw MatchError("Error al solicitar tipo de hechizo:"
                             " fissure es posicional");
}

bool Fissure::isPositional() const {
    return true;
}
