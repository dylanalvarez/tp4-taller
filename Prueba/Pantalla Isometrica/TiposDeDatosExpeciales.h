#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__


#define NoColicion 0

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
#endif
