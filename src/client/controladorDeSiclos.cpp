#include "controladorDeSiclos.h"
#include <thread>

void hiloRecepto(Receptor* receiver){
  receiver->iniciar();
}
void hiloEmisor(Emisor* emisor){
  emisor->iniciar();
}

void ControladorDeSiclos::iniciar(){
  receptorThread = std::thread(hiloRecepto, &receptor);
  emisorThread = std::thread(hiloEmisor, &emisor);
}

void ControladorDeSiclos::terminar(){
  emisor.terminar();
  emisorThread.join();
  receptor.terminar();
  receptorThread.join();
}

ControladorDeSiclos::ControladorDeSiclos(Receptor &receptor2, Emisor &emisor2):
            receptor(receptor2), emisor(emisor2){
}
