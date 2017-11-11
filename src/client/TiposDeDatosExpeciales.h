#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__


#define NoColicion 0
#include <gtkmm.h>
#include <iostream>
#include <vector>
#include "../common/CommunicationUtils.h"

enum Elementos{
  fuego,agua,aire,tierra  };

Elementos toElemento(Communication::Element element);

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
     applySpell2, applyUpgrade, buildTower, startGame
  };
  Type tipo;
  std::string elString;
  std::string elString2;
  int elInt1;
  int elInt2;
  //Mensaje();
};

#endif
