#ifndef __RECEPTOR_H__
#define __RECEPTOR_H__

#include <gtkmm.h>
#include <iostream>
#include "TiposDeDatosExpeciales.h"
#include "OrdenadorDeFichas.h"
#include "menuTorres.h"
#include <vector>
#include "../common/GameClientReceiver.h"
#include "../common/GameClientSocket.h"

class Receptor{
private:
public:
  Receptor(GameClientReceiver& reciver, GameClientSocket& socket);
  void iniciar();
  bool siclo();
  void terminar();
  GameClientReceiver& getReciver();
protected:
  GameClientReceiver& reciver;
  GameClientSocket& socket;
  std::list<Communication::GameState> estados;
  bool seguir = true;
  bool siguiente = true;
};

#endif
