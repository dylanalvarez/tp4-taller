#ifndef __CONTRALADORSICLOS_H__
#define __CONTRALADORSICLOS_H__

#include <gtkmm.h>
#include <iostream>
#include "fListaDeDosLectores.h"
#include "TiposDeDatosExpeciales.h"
#include "OrdenadorDeFichas.h"
#include "menuTorres.h"
#include "receptor.h"
#include "emisor.h"
#include <vector>
#include <thread>

//aun es falso.
class ControladorDeSiclos{
private:
public:
  ControladorDeSiclos(Receptor &receptor2, Emisor &emisor2); //falso
  void iniciar();
  void terminar();
  bool continuar();
  Communication::GameState estadoActual();
protected:
  Receptor &receptor;
  Emisor &emisor;
  std::vector<std::thread> threads;
  bool seguir = true;
};
#endif
