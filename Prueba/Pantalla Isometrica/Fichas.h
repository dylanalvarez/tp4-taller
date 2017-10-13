#ifndef __FFICHAS_H__
#define __FFICHAS_H__

#include <gtkmm.h>
#include <iostream>
#include "sprites.h"
#include "VectorDeSprites.h"

class Ficha{
private:
protected:
 std::vector<FichaSprite> sprites;
 //esto es enificiente para el piso. Pero eficiente para todo lo demas
 int spriteActual;
 int x;
 int y;
 int id;
public:
  Ficha(int x2, int y2, int id2);
  virtual void dibujarme(const Cairo::RefPtr<Cairo::Context>& cr, int desplasamientoX, int desplasamientoY);
  void pulsaion(); //Para los gif
  void cambiarPosicion(int x2, int y2);
  virtual ~Ficha();
  int getId();
};
//FichaTerreno, FichaTorre, FichaEnemigo

#define FichaPisoFirme 0
#define FichaPisoFondo 1
#define FichaPisoEnemigos 2

class FichaTerreno: public Ficha{
private:
protected:
public:
  FichaTerreno(int x2, int y2, int id2, int tipo, VectorDeSprites &sprites);
  void cambiarTipo(int tipo);
};

#define FichaTorreDeTierra 0

class FichaTorre: public Ficha{
private:
protected:
public:
  FichaTorre(int x2, int y2, int id2, int tipo, VectorDeSprites &sprites);
};

#endif
