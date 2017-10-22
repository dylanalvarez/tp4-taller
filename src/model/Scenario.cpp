//
// Created by facundo on 15/10/17.
//

#include "Scenario.h"
#include "Exceptions/TowerError.h"

Scenario::Scenario(Path&& path, std::vector<Vector>&& firm_ground_locations) :
        path(std::move(path)),
        firm_ground_locations(std::move(firm_ground_locations)) {}

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
            if (count != -1 && closest_enemies.size() == count){
                // si es -1 -> devolver todos los que esten en rango
                break;
            }
        }
    }

    return closest_enemies;
}

void Scenario::addEnemy(Enemy& enemy) {
    enemies.push_back(enemy);
}

Scenario::Scenario(Scenario&& other) noexcept : path(std::move(other.path)) {
    this->enemies = std::move(other.enemies);
    this->towers = std::move(other.towers);
    this->firm_ground_locations = std::move(other.firm_ground_locations);
}

Scenario& Scenario::operator=(Scenario&& other) noexcept {
    this->enemies = std::move(other.enemies);
    this->towers = std::move(other.towers);
    this->firm_ground_locations = std::move(other.firm_ground_locations);

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

void Scenario::addTower(Tower* tower) {
    bool can_be_added = false;
    for (Vector& firm_ground : firm_ground_locations){
        if (tower->getPosition() == firm_ground) {
            can_be_added = true;
            break;
        }
    }

    if (can_be_added){
        towers.push_back(tower);
    } else {
        throw TowerError("Error al agregar torre en la posicion: " +
                                 tower->getPosition().to_string() +
                                 ". La posicion ya fue ocupada o no es terreno firme");
    }
}
