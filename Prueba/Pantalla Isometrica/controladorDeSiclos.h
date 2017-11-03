#ifndef __CONTRALADORSICLOS_H__
#define __CONTRALADORSICLOS_H__

#include <gtkmm.h>
#include <iostream>
#include "TiposDeDatosExpeciales.h"
#include "OrdenadorDeFichas.h"
#include "menuTorres.h"
#include <vector>
#include <thread>


class GameClientReceiver {
 protected:
    OrdenadorDeFichas& fichas;
    MenuTorres& menues;
 public:
    GameClientReceiver(OrdenadorDeFichas& fichas2, MenuTorres& menues2);
    void getInitialData(const std::vector<Communication::NameAndID> &matches,
                         const std::vector<Communication::NameAndID> &maps);
    void getMap(std::string &&map);//aun no haec nada.
    void getGameState(const Communication::GameState &gameState);
    void getChatMessage(std::string &&message,
                         std::string &&nickname);
    ~GameClientReceiver();
};

class Emisor{
private:
public:
  void iniciar();
  void terminar();
protected:
  bool seguir = true;
};

class Recptor{
private:
public:
  Recptor(OrdenadorDeFichas& fichas2, MenuTorres& menues2);
  void iniciar();
  bool siclo();
  void terminar();
protected:
  GameClientReceiver reciver;
  std::list<Communication::GameState> estados;
  bool seguir = true;
  bool siguiente = true;
};

//aun es falso.
class ControladorDeSiclos{
private:
public:
  ControladorDeSiclos(OrdenadorDeFichas& fichas2, MenuTorres& menues2); //falso
  void iniciar();
  void terminar();
  bool continuar();
  Communication::GameState estadoActual();
protected:
  Recptor receptor;
  std::vector<std::thread> threads;
  bool seguir = true;
};
#endif
