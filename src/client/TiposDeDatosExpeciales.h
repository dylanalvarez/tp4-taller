#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__


#define NoColicion 0
#include <gtkmm.h>
#include <iostream>
#include <vector>
#include "../common/CommunicationUtils.h"

enum Elementos{
  fuego,agua,aire,tierra  };

enum Hechizo{
  Terraforming, Congelacion, Grieta, Ventisca, Meteorito, Tornado,
  MuroDeFuego, Rayos};

//este es la unica razon por la que esta esta libreraria
struct DatosPantalla{
//corregir idioma
  int width;
  int height;
  int desplasamientoX;
  int desplasamientoY;
};

struct Posicion{
  int X;
  int Y;
};

struct Mensaje {
  enum Type {
    chooseTeam, chooseMap, chooseElement, sendChatMessage, pingTile, applySpell1,
     applySpell2, applyUpgrade, buildTower
  };
  Type tipo;
  std::string elString;
  int elInt1;
  int elInt2;
  Communication::Element elElemento;
  Communication::PositionalPower elPoderPosicional;
  Communication::TargetPower elPoderTargetado;
  Communication::Upgrade laMejora;
  Communication::Tower::Type elTypoDeTorre;
  //Mensaje();
};

#endif
