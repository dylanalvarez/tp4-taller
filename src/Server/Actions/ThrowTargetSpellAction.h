//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_THROWTARGETSPELLACTION_H
#define TOWERDEFENSE_THROWTARGETSPELLACTION_H


#include "Action.h"

class ThrowTargetSpellAction : public Action {
public:
    ThrowTargetSpellAction(std::string& spell, const Player& player,
                           int enemy_id);

    void apply(TowerDefenseGame& game) override;

    ThrowTargetSpellAction(const ThrowTargetSpellAction&) = delete;
    ThrowTargetSpellAction& operator=(const ThrowTargetSpellAction&) = delete;

private:
    const Player& player;
    std::string spell;
    int enemy_id;
};


#endif //TOWERDEFENSE_THROWTARGETSPELLACTION_H
