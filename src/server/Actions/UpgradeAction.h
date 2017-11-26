#ifndef TOWERDEFENSE_UPGRADEACTION_H
#define TOWERDEFENSE_UPGRADEACTION_H


#include "Action.h"

class UpgradeAction : public Action {
public:
    UpgradeAction(const Player &player, const Tower &tower, std::string &&type);

    void apply(Context &context) override;

private:
    const Player &player;
    const Tower &tower;
    std::string type;
};


#endif //TOWERDEFENSE_UPGRADEACTION_H
