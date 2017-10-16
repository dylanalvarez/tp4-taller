//
// Created by facundo on 16/10/17.
//

#include "TowerDefenseGame.h"
#include "Exceptions/EnemyError.h"

TowerDefenseGame::TowerDefenseGame(const std::string &config_file,
                                   const std::string &scenario_file) {
    YAML::Node config = YAML::LoadFile(config_file);
    loadEnemyProperties(config);

    // cargar propiedades de las torres
    // cargar propiedades del escenario

    id = 1;
    Path path({Vector(0,0), Vector(0,5), Vector(3,5),
               Vector(3,2), Vector(-1, 2)});

    scenario = new Scenario(std::move(path));
}

TowerDefenseGame::~TowerDefenseGame(){
    delete scenario;
}

void TowerDefenseGame::addEnemy(const std::string &enemy_type) {
    try{
        EnemyProperties properties = enemies_properties.at(enemy_type);
        Enemy enemy(id++, scenario->getPath(), properties.hp, properties.speed,
                             properties.does_it_fly);
        scenario->addEnemy(std::move(enemy));
    } catch (std::exception& e) {
        throw EnemyError("Error al agregar enemigo -> El tipo: " + enemy_type
                         + " no es un tipo valido");
    }
}

void TowerDefenseGame::loadEnemyProperties(YAML::Node& config) {
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

const std::vector<Enemy> &TowerDefenseGame::getAllEnemies() const {
    return scenario->getAllEnemies();
}

void TowerDefenseGame::moveEnemies() {
    for (Enemy& enemy : scenario->getAllEnemies()){
        enemy.move();
    }
}
