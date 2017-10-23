//
// Created by facundo on 23/10/17.
//

#include "Meteorite.h"

Meteorite::Meteorite(Scenario& scenario, unsigned int cooldown,
                     unsigned int reach, unsigned int dmg,
                     unsigned int dmg_to_nearby_enemies) :
                        scenario(scenario), cooldown(cooldown),
                        dmg(dmg), dmg_to_nearby_enemies(dmg_to_nearby_enemies),
                        reach(reach) {
    is_active = false;
    last_activation_time = 0;
}

void Meteorite::applyEffect(Enemy &enemy) {
    if (difftime(time(nullptr), last_activation_time) < cooldown) { return; }

    enemy.reduceLife(dmg);

    std::vector<Enemy*> enemies = std::move(scenario.getEnemiesInRange(
            Range(enemy.getCurrentPosition()), reach));

    for (Enemy* target : enemies) {
        if (target->getID() == enemy.getID()) { continue; }
        target->reduceLife(dmg_to_nearby_enemies);
    }

    last_activation_time = time(nullptr);
}

bool Meteorite::canBeThrownBy(const std::string &element) {
    return element == "fire";
}

void Meteorite::attack() {}

void Meteorite::applyEffect(const Vector &position) {}

bool Meteorite::isActive() const {
    return is_active;
}
