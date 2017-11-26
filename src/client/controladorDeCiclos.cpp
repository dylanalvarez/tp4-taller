#include "controladorDeCiclos.h"

void hiloRecepto(Receptor *receiver) {
    receiver->iniciar();
}

void hiloEmisor(Emisor *emisor) {
    emisor->iniciar();
}

void controladorDeCiclos::iniciar() {
    receptorThread = std::thread(hiloRecepto, &receptor);
    emisorThread = std::thread(hiloEmisor, &emisor);
}

void controladorDeCiclos::terminar() {
    emisor.terminar();
    emisorThread.join();
    receptor.terminar();
    receptorThread.join();
}

controladorDeCiclos::controladorDeCiclos(Receptor &receptor2, Emisor &emisor2) :
        receptor(receptor2), emisor(emisor2) {
}
