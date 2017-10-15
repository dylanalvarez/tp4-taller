//
// Created by facundo on 15/10/17.
//

#include "Scenario.h"

Scenario::Scenario(Path path) : path(std::move(path)) {}

std::vector<Enemy*> Scenario::getEnemiesInRange(const Range &range,
                                                int count) {
    std::vector<Enemy*> closest_enemies;
    for (Enemy& enemy : enemies){
        if (range.isInRange(enemy.getCurrentPosition())){
            closest_enemies.push_back(&enemy);
            if (closest_enemies.size() == count){
                break;
            }
        }
    }

    return closest_enemies;
}

void Scenario::addEnemy(int id, std::string enemy_type) {
    enemies.emplace_back(id, path, 10, 1, false);
}

Scenario::Scenario(Scenario&& other) noexcept : path(std::move(other.path)) {
    this->enemies = std::move(other.enemies);
}

Scenario& Scenario::operator=(Scenario&& other) noexcept {
    this->path = std::move(other.path);
    this->enemies = std::move(other.enemies);

    return *this;
}
