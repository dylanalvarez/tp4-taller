//
// Created by facundo on 15/10/17.
//

#include "Scenario.h"
#include "Exceptions/TowerError.h"
#include "Exceptions/MatchError.h"

Scenario::Scenario(Path&& path, std::vector<Vector>&& firm_ground_locations) :
        firm_ground_locations(std::move(firm_ground_locations)) {
    paths.push_back(std::move(path));
}

Scenario::Scenario(std::vector<Path> &&paths,
                   std::vector<Vector> &&firm_ground_locations) :
        firm_ground_locations(std::move(firm_ground_locations)),
        paths(std::move(paths)) {}

Scenario::~Scenario() {
    for (auto &tower : towers) {
        delete tower;
    }
}

std::vector<Enemy*> Scenario::getEnemiesInRange(const Range &range,
                                                int count) {
    std::vector<Enemy*> closest_enemies;
    for (Enemy& enemy : enemies){
        if (range.isInRange(enemy.getCurrentPosition())) {
            closest_enemies.push_back(&enemy);
            if (count != -1 && (int)closest_enemies.size() == count) {
                // si no se deben devolver todos y se llego a la
                // cantidad a devolver salir
                break;
            }
        }
    }

    return closest_enemies;
}

void Scenario::addEnemy(Enemy& enemy) {
    enemies.push_back(enemy);
}

Scenario::Scenario(Scenario&& other) noexcept {
    this->paths = std::move(other.paths);
    this->enemies = std::move(other.enemies);
    this->towers = std::move(other.towers);
    this->firm_ground_locations = std::move(other.firm_ground_locations);
}

Scenario& Scenario::operator=(Scenario&& other) noexcept {
    this->paths = std::move(other.paths);
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

Path &Scenario::getPath(unsigned int number) {
    return paths.at(number - 1);
}

void Scenario::addTower(Tower* tower) {
    for (Vector& firm_ground : firm_ground_locations) {
        if (tower->getPosition() == firm_ground) {
            towers.push_back(tower);
            // como ya se ocupa, se saca de las tierras firmes disponibles
            firm_ground_locations.erase(std::remove(firm_ground_locations.begin(),
                                                    firm_ground_locations.end(),
                                                    tower->getPosition()));
            return;
        }
    }

    throw TowerError("Error al agregar torre en la posicion: " +
                                 tower->getPosition().to_string() +
                                 ". La posicion ya fue ocupada o no es terreno firme");
}

void Scenario::levelupTower(const Tower& tower_to_lvl, const std::string& type) {
    for (Tower* tower : towers) {
        if (tower == &tower_to_lvl) {
            tower->levelup(type);
        }
    }
}

int Scenario::cleanEnemies() {
    std::vector<Enemy> not_dead_enemies;
    int deads_count = 0;
    for (Enemy& enemy: enemies){
        if (!enemy.isDead()){
            not_dead_enemies.push_back(enemy);
        } else { deads_count++; }
    }

    std::swap(enemies, not_dead_enemies);

    return deads_count;
}

void Scenario::addFirmGround(const Vector &position) {
    // no se puede agregar en un camino
    for (Path& path : paths) {
        if (path.containsPosition(position)) {
            throw MatchError("Error al agregar terreno firme: la posicion" +
                             position.to_string() +
                             " esta ocupada por camino");
        }
    }

    // no se puede agregar en tierra firme
    for (auto& vector : firm_ground_locations){
        if (vector == position) {
            throw MatchError("Error al agregar terreno firme: la posicion" +
                             position.to_string() +
                             " esta ocupada por terreno firme");
        }
    }

    // no se puede agregar en posicion ocupada por torre
    for (auto& tower : towers){
        if (tower->getPosition() == position) {
            throw MatchError("Error al agregar terreno firme: la posicion" +
                             position.to_string() +
                             " esta ocupada por torre");
        }
    }

    firm_ground_locations.push_back(position);
}
