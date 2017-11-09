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
