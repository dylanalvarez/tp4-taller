//
// Created by facundo on 23/10/17.
//

#include "FireWall.h"

FireWall::FireWall(Scenario& scenario, unsigned int cooldown,
                   unsigned int dmg, unsigned int duration) :
        scenario(scenario), cooldown(cooldown), duration(duration), dmg(dmg) {
    is_active = false;
}

void FireWall::applyEffect(const Vector &position) {
    is_active = true;
    this->position = position;
    last_activation_time = time(nullptr);
}

void FireWall::applyEffect(Enemy &enemy) {}

bool FireWall::canBeThrownBy(const std::string &element) {
    return element == "fire";
}

void FireWall::attack() {
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
    }
}
