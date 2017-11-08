//
// Created by facundo on 31/10/17.
//

#include <iostream>
#include <syslog.h>
#include "BuildTowerAction.h"

BuildTowerAction::BuildTowerAction(const Player &player,
                                   std::string &element,
                                   Vector position) : player(player),
                                                      element(std::move(element)),
                                                      position(position) {}

void BuildTowerAction::apply(Context& context) {
    try {
        context.getGame().addTower(player, element, position);
    } catch (std::exception& e) {
        syslog(LOG_CRIT, "Error: %s\n", e.what());
        std::cerr << "Error al agregar torre, ver syslog para mas informacion\n";
    }
}
