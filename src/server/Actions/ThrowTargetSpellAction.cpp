//
// Created by facundo on 31/10/17.
//

#include <iostream>
#include <syslog.h>
#include "ThrowTargetSpellAction.h"
#include "../../model/Exceptions/MatchError.h"

ThrowTargetSpellAction::ThrowTargetSpellAction(std::string &spell,
                                               const Player &player,
                                               int enemy_id) : player(player),
                                                               spell(std::move(spell)),
                                                               enemy_id(enemy_id) {}

void ThrowTargetSpellAction::apply(Context& context) {
    try {
        context.getGame().throwSpell(player, spell, enemy_id);
    } catch (MatchError& e) {
        std::cerr << "Error al aplicar hechizo al enemigo: " +
                     std::to_string(enemy_id) + ", ver syslog para mas informacion\n";
        syslog(LOG_CRIT, "Error: %s\n", e.what());
    }
}
