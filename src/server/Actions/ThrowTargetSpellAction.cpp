//
// Created by facundo on 31/10/17.
//

#include "ThrowTargetSpellAction.h"

ThrowTargetSpellAction::ThrowTargetSpellAction(std::string &spell,
                                               const Player &player,
                                               int enemy_id) : player(player),
                                                               spell(std::move(spell)),
                                                               enemy_id(enemy_id) {}

void ThrowTargetSpellAction::apply(Context& context) {
    context.getGame().throwSpell(player, spell, enemy_id);
}
