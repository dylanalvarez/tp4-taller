//
// Created by facundo on 24/10/17.
//

#include "Ray.h"

Ray::Ray(Scenario &scenario, unsigned int cooldown, unsigned int min_dmg,
         unsigned int max_dmg) : Spell(scenario, cooldown),
                                 min_dmg(min_dmg),
                                 max_dmg(max_dmg) {}

void Ray::applyEffect(const Vector &position) {}

void Ray::applyEffect(Enemy &enemy) {
    if (isOnCooldown()) { return; }

    // sera usada para obtener un "seed" para el engine generador de numeros
    std::random_device rd;
    // engine seeded with rd
    std::mt19937 gen(rd());
    // distribucion uniforme
    std::uniform_int_distribution<> distribution(min_dmg, max_dmg);

    enemy.reduceLife((unsigned)distribution(gen));

    last_activation_time = time(nullptr);
}

bool Ray::canBeThrownBy(const std::string &element) {
    return element == "air";
}

void Ray::attack() {}

bool Ray::isActive() const {
    return is_active;
}
