//
// Created by facundo on 23/10/17.
//

#include "FireWall.h"

FireWall::FireWall(Scenario& scenario, unsigned int cooldown,
                   unsigned int dmg, unsigned int duration) :
        Spell(scenario, cooldown),
        duration(duration),
        dmg(dmg) {}

void FireWall::applyEffect(const Vector &position) {
    activate(position);
}

void FireWall::applyEffect(Enemy &enemy) {}

bool FireWall::canBeThrownBy(const std::string &element) {
    return element == "fire";
}

void FireWall::attack() {
    checkIfIsActive(duration);

    if (!is_active) { return; }

    for (Enemy* enemy : scenario.getEnemiesInRange(Range(position, 0))) {
        enemy->reduceLife(dmg);
    }
}

bool FireWall::isActive() const {
    return is_active;
}
