//
// Created by facundo on 05/11/17.
//

#include "UpgradeAction.h"

UpgradeAction::UpgradeAction(const Player& palyer, const Tower& tower,
                             std::string &type) :
        player(player), tower(tower), type(type) {}

void UpgradeAction::apply(Context &context) {
    try {
        context.getGame().levelupTower(tower, type, player);
    } catch (std::exception& e) {
        // la torre no existe
    }
}
