//
// Created by facundo on 31/10/17.
//

#include "AddEnemyAction.h"

AddEnemyAction::AddEnemyAction(std::string &enemy_type,
                               unsigned int path_number) :
        enemy_type(enemy_type), path_number(path_number) {}

void AddEnemyAction::apply(TowerDefenseGame &game) {
    game.addEnemy(enemy_type, path_number);
}
