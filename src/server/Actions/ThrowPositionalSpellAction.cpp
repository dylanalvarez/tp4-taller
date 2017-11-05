//
// Created by facundo on 31/10/17.
//

#include "ThrowPositionalSpellAction.h"

ThrowPositionalSpellAction::ThrowPositionalSpellAction(std::string &spell,
                                   const Player& player,
                                   Vector& vector) : player(player),
                                                     spell(std::move(spell)),
                                                     position(vector) {}

void ThrowPositionalSpellAction::apply(Context& context) {
    context.getGame().throwSpell(player, spell, position);
}
