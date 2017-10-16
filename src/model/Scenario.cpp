//
// Created by facundo on 15/10/17.
//

#include "Scenario.h"
#include "Exceptions/EnemyError.h"

Scenario::Scenario(Path path, YAML::Node config) : path(std::move(path)) {
    // TODO obtener propiedades del nodo YAML
    typedef std::pair<std::string, EnemyProperties> pair;

    // green_demon
    EnemyProperties properties(300, 1, false);
    pair green_demon("green_demon", properties);
    // abmonible
    properties.hp = 200;
    pair abmonible("abmonible", properties);
    // goat_man
    properties.hp = 100;
    properties.speed = 2;
    pair goat_man("goat_man", properties);
    // undead
    properties.hp = 20;
    properties.speed = 10;
    pair undead("undead", properties);
    // bloody_hawk
    properties.hp = 100;
    properties.speed = 4;
    properties.does_it_fly = true;
    pair bloody_hawk("bloody_hawk", properties);
    // spectrum
    properties.speed = 6;
    pair spectrum("spectrum", properties);

    enemies_properties.insert(abmonible);
    enemies_properties.insert(green_demon);
    enemies_properties.insert(bloody_hawk);
    enemies_properties.insert(spectrum);
    enemies_properties.insert(goat_man);
    enemies_properties.insert(undead);
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

void Scenario::addEnemy(int id, std::string enemy_type) {
    for (Enemy& enemy : enemies){
        if (enemy.getID() == id){
            throw EnemyError("Error al añadir enemigo al escenario:"
                                     " el id" + std::to_string(id) + "ya existe");
        }
    }

    try{
        EnemyProperties properties = enemies_properties.at(enemy_type);
        enemies.emplace_back(id, path, properties.hp, properties.speed,
                             properties.does_it_fly);
    } catch (std::exception& e) {
       throw EnemyError("Error al agregar enemigo -> El tipo: " + enemy_type
                        + " no es un tipo valido");
    }
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
