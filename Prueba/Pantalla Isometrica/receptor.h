#ifndef __RECEPTOR_H__
#define __RECEPTOR_H__

#include <gtkmm.h>
#include <iostream>
#include "TiposDeDatosExpeciales.h"
#include "OrdenadorDeFichas.h"
#include "menuTorres.h"
#include <vector>


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

class Receptor{
private:
public:
  Receptor(OrdenadorDeFichas& fichas2, MenuTorres& menues2);
  void iniciar();
  bool siclo();
  void terminar();
protected:
  GameClientReceiver reciver;
  std::list<Communication::GameState> estados;
  bool seguir = true;
  bool siguiente = true;
};

#endif
