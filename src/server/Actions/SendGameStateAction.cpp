#include "SendGameStateAction.h"

SendGameStateAction::SendGameStateAction(const Communication::GameState &state)
        : gameState(state) {}

void SendGameStateAction::apply(Context &context) {
    context.getSocket().sendGameState(gameState);
}
