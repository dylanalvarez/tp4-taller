#include <iostream>
#include <syslog.h>
#include "ThrowPositionalSpellAction.h"
#include "../../model/Exceptions/MatchError.h"

ThrowPositionalSpellAction::ThrowPositionalSpellAction(std::string &spell,
                                                       const Player &player,
                                                       Vector &vector) : player(
        player),
                                                                         spell(std::move(
                                                                                 spell)),
                                                                         position(
                                                                                 vector) {}

void ThrowPositionalSpellAction::apply(Context &context) {
    try {
        context.getGame().throwSpell(player, spell, position);
    } catch (MatchError &e) {
        std::cerr << "Error al aplicar hechizo en la posicion: " +
                     position.to_string() +
                     ", ver syslog para mas informacion\n";
        syslog(LOG_CRIT, "Error: %s\n", e.what());
    }
}
