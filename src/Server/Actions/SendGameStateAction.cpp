//
// Created by facundo on 03/11/17.
//

#include "SendGameStateAction.h"

SendGameStateAction::SendGameStateAction(const Communication::GameState &) :
        gameState(gameState) {}

void SendGameStateAction::apply(Context& context) {
    context.getSocket().sendGameState(gameState);
}
