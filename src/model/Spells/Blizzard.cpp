//
// Created by facundo on 23/10/17.
//

#include "Blizzard.h"

Blizzard::Blizzard(Scenario& scenario, unsigned int cooldown,
                   unsigned int duration, unsigned int dmg,
                   unsigned int speed_reduction,
                   unsigned int speed_reduction_duration) :
Spell(scenario, cooldown),
dmg(dmg),
duration(duration),
speed_reduction(speed_reduction),
speed_reduction_duration(speed_reduction_duration) {}

void Blizzard::applyEffect(const Vector &position) {
   activate(position);
}

void Blizzard::applyEffect(Enemy &enemy) {}

bool Blizzard::canBeThrownBy(const std::string &element) {
    return element == "water";
}

void Blizzard::attack() {
    checkIfIsActive(duration);

    if (!is_active) { return; }

    for (Enemy* enemy : scenario.getEnemiesInRange(Range(position, 0))) {
        enemy->reduceLife(dmg);
        enemy->reduceSpeed(speed_reduction, speed_reduction_duration);
    }
}

bool Blizzard::isActive() const {
    return is_active;
}
