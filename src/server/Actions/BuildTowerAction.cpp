//
// Created by facundo on 31/10/17.
//

#include "BuildTowerAction.h"

BuildTowerAction::BuildTowerAction(const Player &player,
                                   std::string &element,
                                   Vector position) : player(player),
                                                      element(std::move(element)),
                                                      position(position) {}

void BuildTowerAction::apply(Context& context) {
    context.getGame().addTower(player, element, position);
}