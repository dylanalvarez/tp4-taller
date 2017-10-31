#include "controladorDeSiclos.h"
#include <thread>

void ControladorDeSiclos::iniciar(){
  //C Solo me permite dormir por 1 segundo como minimo.
  while (seguir) {
    if (siguiente) {
      siguiente = false;
      siclo();
      //acara irira un recivir
    }
  }
}

void ControladorDeSiclos::terminar(){
  seguir = false;
}

ControladorDeSiclos::ControladorDeSiclos(int id, OrdenadorDeFichas& fichas2): fichas(fichas2){
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

Communication::GameState ControladorDeSiclos::estadoActual(){
  auto retorno = estados.front();
  estados.pop_front();
  return retorno;
}

bool ControladorDeSiclos::siclo(){
  if (estados.size() <0 )
    return false;
  auto aux = estadoActual();
  for (auto it = aux.enemy.begin() ; it != aux.enemy.end(); ++it)
    fichas.actualizarEnemigo(*it);
/*
  for (auto it = aux.towers.begin() ; it != aux.towers.end(); ++it)
    fichas.actualizarEnemigo(*it);
  for (auto it = aux.positionalPowers.begin() ; it != aux.positionalPowers.end(); ++it)
    fichas.actualizarEnemigo(*it);
  for (auto it = aux.targetPowers.begin() ; it != aux.targetPowers.end(); ++it)
    fichas.actualizarEnemigo(*it);
*/
  return true;
}

bool ControladorDeSiclos::continuar(){
  siguiente = true;
  return true;
}
