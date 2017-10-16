//
// Created by facundo on 15/10/17.
//

#include "Scenario.h"

Scenario::Scenario(Path path) : path(std::move(path)) {}

Scenario::~Scenario() {
    for (auto &tower : towers) {
        delete tower;
    }
}

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

void Scenario::addEnemy(Enemy enemy) {
    enemies.push_back(std::move(enemy));
}

Scenario::Scenario(Scenario&& other) noexcept : path(std::move(other.path)) {
    this->enemies = std::move(other.enemies);
}

Scenario& Scenario::operator=(Scenario&& other) noexcept {
    this->path = std::move(other.path);
    this->enemies = std::move(other.enemies);

    return *this;
}

std::vector<Enemy> &Scenario::getAllEnemies() {
    return enemies;
}

std::vector<Tower*>& Scenario::getTowers() {
    return towers;
}

Path &Scenario::getPath() {
    return path;
}

void Scenario::addTower(Tower* tower, const Vector &position) {

}
