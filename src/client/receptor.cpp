#include "receptor.h"

//receptor
Receptor::Receptor(GameClientReceiver& reciver, GameClientSocket& socket):
      reciver(reciver), socket(socket){
  /*Communication::Enemy aux(Communication::Enemy::Type::abmonible, 1, 0, 0);
  Communication::GameState aux2;
  aux2.state = Communication::GameState::State::ongoing;
  for (size_t i = 0; i < 880; i++) {
    aux2.enemies.clear();
    aux.x = i;
    aux2.enemies.push_back(aux);
    estados.push_back(aux2);
  }
  aux2.enemies.clear();
  estados.push_back(aux2);*/
}
void Receptor::iniciar(){
  socket.run();
 /*while (seguir) {
    if (siguiente) {
      siguiente = false;
      auto aux = estados.front();
      estados.pop_front();
      reciver.getGameState(aux);
    }
  }*/
}
bool Receptor::siclo(){
  if (estados.empty() )
    return false;
  siguiente = true;
  return true;
}
void Receptor::terminar(){
  socket.disconnect();
  seguir = false;
}
GameClientReceiver& Receptor::getReciver(){
  return reciver;
}
