#ifndef __CONTRALADORSICLOS_H__
#define __CONTRALADORSICLOS_H__

#include <gtkmm.h>
#include <iostream>
#include "TiposDeDatosExpeciales.h"
#include "OrdenadorDeFichas.h"
#include <vector>

//aun es falso.
class ControladorDeSiclos{
private:
public:
  ControladorDeSiclos(int id, OrdenadorDeFichas& fichas2); //falso
  void iniciar();
  void terminar();
  bool siclo();
  bool continuar();
  Communication::GameState estadoActual();
protected:
  OrdenadorDeFichas& fichas;
  std::list<Communication::GameState> estados;
  bool seguir = true;
  bool siguiente = true;
};
#endif
