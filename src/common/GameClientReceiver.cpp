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
  fichas.preprarParaActualizacion();
  for (auto it = gameState.enemies.begin() ; it != gameState.enemies.end(); ++it)
    fichas.actualizarEnemigo(*it);
/*
  for (auto it = aux.towers.begin() ; it != aux.towers.end(); ++it)
    fichas.actualizarEnemigo(*it);
  for (auto it = aux.positionalPowers.begin() ; it != aux.positionalPowers.end(); ++it)
    fichas.actualizarEnemigo(*it);
  for (auto it = aux.targetPowers.begin() ; it != aux.targetPowers.end(); ++it)
    fichas.actualizarEnemigo(*it);
*/
}

void GameClientReceiver::getChatMessage(std::string &&message,
                     std::string &&nickname){
    menues.recivirMensajeChat(nickname + message);
}

GameClientReceiver::~GameClientReceiver() {
}
