//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_THROWSPELLACTION_H
#define TOWERDEFENSE_THROWSPELLACTION_H


#include "Action.h"

class ThrowPositionalSpellAction : public Action {
public:
    ThrowPositionalSpellAction(std::string& spell, const Player& player,
                               Vector& vector);

    void apply(TowerDefenseGame& game) override;

    ThrowPositionalSpellAction(const ThrowPositionalSpellAction&) = delete;
    ThrowPositionalSpellAction& operator=(const ThrowPositionalSpellAction&)
                                                                    = delete;

private:
    const Player& player;
    std::string spell;
    Vector position;
};


#endif //TOWERDEFENSE_THROWSPELLACTION_H
