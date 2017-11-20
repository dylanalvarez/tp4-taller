//
// Created by facundo on 23/10/17.
//

#include "Freezing.h"
#include "../Exceptions/MatchError.h"

Freezing::Freezing(Scenario &scenario, unsigned int cooldown,
                   unsigned int duration) :
        Spell(scenario, cooldown), duration(duration) {}

void Freezing::applyEffect(const Vector &position) {}

void Freezing::applyEffect(Enemy &enemy) {
    if (isOnCooldown()) { return; }

    enemy.reduceSpeed(100, duration);
    is_active = true;
    last_activation_time = time(nullptr);
    target_id = enemy.getID();
}

bool Freezing::canBeThrownBy(const std::string &element) {
    return element == "water";
}

void Freezing::update() { is_active = false; }

bool Freezing::isActive() const {
    return is_active;
}

Communication::PositionalPower::Type Freezing::getPositionalType() const {
    throw MatchError("Error al solicitar tipo de hechizo:"
                             " freezing no es posicional");
}

Communication::TargetPower::Type Freezing::getTargetType() const {
    return Communication::TargetPower::Type::freezing;
}

bool Freezing::isPositional() const {
    return false;
}
