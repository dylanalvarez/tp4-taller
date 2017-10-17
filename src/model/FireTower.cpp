//
// Created by facundo on 10/10/17.
//

#include <iostream>
#include "FireTower.h"
#include "Enemy.h"
#include "Scenario.h"

FireTower::FireTower(int id, const Vector p, const YAML::Node& properties,
                     Scenario& scenario) :
        Tower(id, p, properties, scenario) {
    this->position = p;
    range = Range(position, 3);
    dmg = 6;
    dmg_to_nearby_enemies = 3;
    // un ataque cada 3 segundos
    attack_cooldown = 3;
    last_attack_time = 0;
    current_target = nullptr;
}

FireTower::~FireTower() = default;

void FireTower::attack() {
    // si todavia no paso el cooldown desde el ultimo ataque, salir
    if (difftime(time(nullptr), last_attack_time) < attack_cooldown) { return; }

    std::vector<Enemy*> enemies = scenario.getEnemiesInRange(range);
    if (enemies.empty()) { return; }

    if (current_target) {
        if (current_target->getHealthPoints() == 0){
            // cambiar objetivo
            current_target = enemies[0];
        }
    } else {
        current_target = enemies[0];
    }

    current_target->reduceLife(dmg);

    // daño a los enemigos cercanos
    for (int i = 1; i < enemies.size(); i++) {
        if ((enemies[i]->getCurrentPosition() -
                enemies[0]->getCurrentPosition()).getNorm() <= 1){
            enemies[i]->reduceLife(dmg_to_nearby_enemies);
        }
    }

    last_attack_time = time(nullptr);
}
