#include "receptor.h"

//receptor
Receptor::Receptor(GameClientReceiver &reciver, GameClientSocket &socket) :
        reciver(reciver), socket(socket) {
}

void Receptor::iniciar() {
    socket.start();
}

void Receptor::terminar() {
    socket.disconnect();
    socket.join();
    seguir = false;
}

GameClientReceiver &Receptor::getReceiver() {
    return reciver;
}
