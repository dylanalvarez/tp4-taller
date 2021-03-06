#ifndef TOWERDEFENSE_THROWTARGETSPELLACTION_H
#define TOWERDEFENSE_THROWTARGETSPELLACTION_H


#include "Action.h"

class ThrowTargetSpellAction : public Action {
public:
    ThrowTargetSpellAction(std::string &spell, const Player &player,
                           int enemy_id);

    void apply(Context &context) override;

    ThrowTargetSpellAction(const ThrowTargetSpellAction &) = delete;

    ThrowTargetSpellAction &operator=(const ThrowTargetSpellAction &) = delete;

private:
    const Player &player;
    std::string spell;
    int enemy_id;
};


#endif //TOWERDEFENSE_THROWTARGETSPELLACTION_H
