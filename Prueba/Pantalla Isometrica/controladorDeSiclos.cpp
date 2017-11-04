#include "controladorDeSiclos.h"
#include <thread>

void hiloRecepto(Receptor* receiver){
  receiver->iniciar();
}
void hiloEmisor(Emisor* emisor){
  emisor->iniciar();
}

void ControladorDeSiclos::iniciar(){
  threads.push_back(std::thread(hiloRecepto, &receptor));
  threads.push_back(std::thread(hiloEmisor, &emisor));
}

void ControladorDeSiclos::terminar(){
  receptor.terminar();
  emisor.terminar();
  for (auto& th : threads) th.join();
}

ControladorDeSiclos::ControladorDeSiclos(Receptor &receptor2, Emisor &emisor2):
            receptor(receptor2), emisor(emisor2){
}

bool ControladorDeSiclos::continuar(){
<<<<<<< HEAD
  receptor.siclo();
  emisor.siclo();
=======
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
>>>>>>> ab5c53c2e83d5575106434ac4f7ca6340b19bed3
  return true;
}
