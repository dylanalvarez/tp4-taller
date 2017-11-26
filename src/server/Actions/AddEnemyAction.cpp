#include "AddEnemyAction.h"

AddEnemyAction::AddEnemyAction(const std::string &enemy_type,
                               unsigned int path_number) :
        enemy_type(enemy_type), path_number(path_number) {}

void AddEnemyAction::apply(Context &context) {
    context.getGame().addEnemy(enemy_type, path_number);
}
