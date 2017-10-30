#include "controladorDeSiclos.h"
#include <thread>

void ControladorDeSiclos::iniciar(){
  /*while (seguir) {
    std::this_thread::sleep_for (std::chrono::seconds(1));
     pulso.emit();
  }*/
}

void ControladorDeSiclos::terminar(){
  //seguir = false;
}

ControladorDeSiclos::ControladorDeSiclos(int id, OrdenadorDeFichas& fichas2): fichas(fichas2){
  Communication::Enemy aux;
  aux.type = Communication::Enemy::Type::abmonible;
  aux.x = 0;
  aux.y = 0;
  aux.id = 1;
  for (size_t i = 0; i < 880; i++) {
    aux.x = i;
    posiciones.push_back(aux);
  }
}

Communication::Enemy ControladorDeSiclos::estadoActual(){
  auto retorno = posiciones.front();
  posiciones.pop_front();
  return retorno;
}

bool ControladorDeSiclos::siclo(){
  fichas.actualizarEnemigo(estadoActual());
  if (posiciones.size() <0 )
    return false;
  return true;
}
