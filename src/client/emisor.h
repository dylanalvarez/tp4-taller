#ifndef __EMISOR_H__
#define __EMISOR_H__

#include <gtkmm.h>
#include <iostream>
#include "fListaDeDosLectores.h"
#include <vector>
#include <thread>

class Emisor{
private:
public:
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
  void cosntruirTorre(int x, int y, Communication::Tower::Type tipo);
protected:
  ColaBloqueante cola;
  bool seguir = true;
  bool siguiente = true;
};
#endif
