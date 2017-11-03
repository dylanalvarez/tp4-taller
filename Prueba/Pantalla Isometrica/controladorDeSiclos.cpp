#include "controladorDeSiclos.h"
#include <thread>

void hiloRecepto(Recptor* receiver){
  receiver->iniciar();
}

void ControladorDeSiclos::iniciar(){
  threads.push_back(std::thread(hiloRecepto, &receptor));
}

void ControladorDeSiclos::terminar(){
  receptor.terminar();
  for (auto& th : threads) th.join();
}

ControladorDeSiclos::ControladorDeSiclos(OrdenadorDeFichas& fichas2,
   MenuTorres& menues2): receptor(fichas2, menues2){
}

bool ControladorDeSiclos::continuar(){
  return receptor.siclo();
}

//receptor
Recptor::Recptor(OrdenadorDeFichas& fichas2, MenuTorres& menues2):
      reciver(fichas2, menues2){
  Communication::Enemy aux;
  Communication::GameState aux2;
  aux2.state = Communication::GameState::State::ongoing;
  aux.type = Communication::Enemy::Type::abmonible;
  aux.x = 0;
  aux.y = 0;
  aux.id = 1;
  for (size_t i = 0; i < 880; i++) {
    aux2.enemy.clear();
    aux.x = i;
    aux2.enemy.push_back(aux);
    estados.push_back(aux2);
  }
}
void Recptor::iniciar(){
  while (seguir) {
    if (siguiente) {
      siguiente = false;
      auto aux = estados.front();
      estados.pop_front();
      reciver.getGameState(aux);
    }
  }
}

bool ControladorDeSiclos::siclo(){
  if (estados.empty())
    return false;
  siguiente = true;
  return true;
}
void Recptor::terminar(){
  seguir = false;
}




//GameClientReceiver
GameClientReceiver::GameClientReceiver(OrdenadorDeFichas& fichas2,
   MenuTorres& menues2): fichas(fichas2), menues(menues2){
   }

void GameClientReceiver::getInitialData(const std::vector<Communication::NameAndID> &matches,
                     const std::vector<Communication::NameAndID> &maps){
                     }
void GameClientReceiver::getMap(std::string &&map){
}//aun no haec nada.
void GameClientReceiver::getGameState(const Communication::GameState &gameState){
  for (auto it = gameState.enemy.begin() ; it != gameState.enemy.end(); ++it)
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
                     }
GameClientReceiver::~GameClientReceiver(){
}
