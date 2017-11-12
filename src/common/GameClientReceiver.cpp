#include "GameClientReceiver.h"
#include "Exception.h"

GameClientReceiver::GameClientReceiver(OrdenadorDeFichas& fichas2,
        MenuTorres& menues2, GestionadorDeVentanas& ventanas2,
        PantallaDeInicio& inicio2, PantallaDeElementos& elemento2):
        fichas(fichas2), menues(menues2), ventanas(ventanas2), inicio(inicio2),
        elemento(elemento2){
   }

void GameClientReceiver::getInitialData(
        const std::vector<Communication::NameAndID> &matches,
        const std::vector<Communication::NameAndID> &maps) {
          inicio.cargarDatos(matches,maps);
}

void GameClientReceiver::getMap(std::string &&map) {
  ventanas.TerminarPantallaDeInicio();
  fichas.cargarMapa(map);
}

void GameClientReceiver::getGameState(const Communication::GameState &gameState){
  fichas.actualizar(gameState);
  menues.actualizarPoderes(gameState);
  ventanas.actualizar(gameState);
}

void GameClientReceiver::getChatMessage(std::string &&message,
                     std::string &&nickname){
    menues.recivirMensajeChat(nickname + message);
}

GameClientReceiver::~GameClientReceiver() = default;

void GameClientReceiver::getUnavailableElement(
        const Communication::Element &element, std::string &&username) {
    elemento.elementoSeleccionado(toElemento(element));
    menues.agregarElemento(toElemento(element), username);
}

void GameClientReceiver::getPing(int x, int y) {
    fichas.agregarPing(x,y);
}
