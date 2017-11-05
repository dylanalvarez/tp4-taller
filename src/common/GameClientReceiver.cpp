#include "GameClientReceiver.h"
#include "Exception.h"

GameClientReceiver::GameClientReceiver() {
    throw Exception("Not yet implemented");
}

void GameClientReceiver::getInitialData(
        const std::vector<Communication::NameAndID> &matches,
        const std::vector<Communication::NameAndID> &maps) {
    throw Exception("Not yet implemented");
}

void GameClientReceiver::getMap(std::string &&map) {
    throw Exception("Not yet implemented");
}

void
GameClientReceiver::getGameState(const Communication::GameState &gameState) {
    throw Exception("Not yet implemented");
}

void GameClientReceiver::getChatMessage(std::string &&message,
                                        std::string &&nickname) {
    throw Exception("Not yet implemented");
}

GameClientReceiver::~GameClientReceiver() {
    throw Exception("Not yet implemented");
}
