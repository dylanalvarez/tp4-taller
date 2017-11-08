#ifndef __EMISOR_H__
#define __EMISOR_H__

#include <gtkmm.h>
#include <iostream>
#include "fListaDeDosLectores.h"
#include "TiposDeDatosExpeciales.h"
#include <vector>
#include <thread>
class GameClientSocket;

class Emisor{
private:
public:
  //Emisor(GameClientReceiver &receiver, Socket &&socket);
  void cargarSocket(GameClientSocket* socket2); //esto se debe poder mejorar en algun futuro.
  void iniciar();
  bool siclo();
  void terminar();
  void elegirEquipo(std::string &nickname, int teamID);
  void elegirMapa(std::string &nickname, int mapID);
  void elegirElemento(Communication::Element elemento);
  void enviarMensajeDeChat(std::string &mensaje);
  void pingear(int x, int y);
  void lansarEchizo(Communication::PositionalPower poder);
  void lansarEchizo(Communication::TargetPower poder);
  void upgraTorre(Communication::Upgrade upgrade);
  void cosntruirTorre(int x, int y, std::string tipo);
protected:
  GameClientSocket* socket;
  ColaBloqueante cola;
  bool seguir = true;
  bool siguiente = true;
};
#endif
