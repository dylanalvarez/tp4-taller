#ifndef __EMISOR_H__
#define __EMISOR_H__

#include <gtkmm.h>
#include <iostream>
#include "ColaBloqueante.h"
#include "TiposDeDatosExpeciales.h"
#include <vector>
#include <thread>
class GameClientSocket;

class Emisor{
public:
  void cargarSocket(GameClientSocket* socket2);
  void iniciar();
  bool ciclo();
  void terminar();
  void elegirEquipo(std::string nickname, int teamID);
  void elegirMapa(std::string nickname, std::string mapName, int mapID);
  void elegirElemento(std::string tipo);
  void empesarJuego();
  void enviarMensajeDeChat(std::string mensaje);
  void pingear(int x, int y);
  void lanzarEchizo(int x, int y, std::string tipo);
  void lanzarEchizo(int id, std::string tipo);
  void upgraTorre(int id, std::string tipo);
  void cosntruirTorre(int x, int y, std::string tipo);
private:
  GameClientSocket* socket;
  ColaBloqueante cola;
  bool seguir = true;
  bool siguiente = true;
};
#endif
