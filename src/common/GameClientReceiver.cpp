#include "GameClientReceiver.h"
#include "Exception.h"

GameClientReceiver::GameClientReceiver(OrdenadorDeFichas& fichas2,
   MenuTorres& menues2): fichas(fichas2), menues(menues2){
   }

void GameClientReceiver::getInitialData(
        const std::vector<Communication::NameAndID> &matches,
        const std::vector<Communication::NameAndID> &maps) {
          printf("Inicio Mapa\n");
  //  throw Exception("Not yet implemented");
}

void GameClientReceiver::getMap(std::string &&map) {
  //  throw Exception("Not yet implemented");
            printf("Nombre Mapa\n");
}

void GameClientReceiver::getGameState(const Communication::GameState &gameState){
  fichas.actualizar(gameState);
  menues.actualizarPoderes(gameState);
}

void GameClientReceiver::getChatMessage(std::string &&message,
                     std::string &&nickname){
    menues.recivirMensajeChat(nickname + message);
}

GameClientReceiver::~GameClientReceiver() = default;

void GameClientReceiver::getUnavailableElement(
        const Communication::Element &element, std::string &&username) {
    throw Exception("Not yet implemented");
}

void GameClientReceiver::getPing(int x, int y) {
    throw Exception("Not yet implemented");
}
