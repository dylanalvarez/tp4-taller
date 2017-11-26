#include "UpgradeAction.h"

UpgradeAction::UpgradeAction(const Player &player, const Tower &tower,
                             std::string &&type) :
        player(player), tower(tower), type(std::move(type)) {}

void UpgradeAction::apply(Context &context) {
    try {
        context.getGame().levelupTower(tower, type, player);
    } catch (std::exception &e) {
        // la torre no existe
    }
}
