#ifndef __FFICHAS_H__
#define __FFICHAS_H__

#include <gtkmm.h>
#include <iostream>
#include "sprites.h"
#include "VectorDeSprites.h"
#include "TiposDeDatosExpeciales.h"

//corregir Srpites y sprites

class Ficha{
 private:
 protected:
  std::vector<Sprite> sprites;
  //esto es enificiente para el piso. Pero eficiente para todo lo demas
  int spriteActual;
  int x;
  int y;
  int id;
  int tipo;
  int medioLargoX;
  int medioAltoY;
  bool destrulleme = false;
 public:
  Ficha();
  Ficha(int x2, int y2, int id2, int tipo2);
  Ficha(const Ficha &p);
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& cr, DatosPantalla datosActuales);
  virtual void ejecutarSicloDeAnimacion(); //Para los gif
  void cambiarPosicion(int x2, int y2);
  virtual ~Ficha();
  int getId() const;
  int getTipo() const;
  bool colisionaConmigo(int x2, int y2);
  void imprimierCordenadas() const;   //echa para revisar nada mas. Quitar despues.
  Posicion getPosicion() const;
  bool siguesVivo() const; //Para los gif
  void setDestrulleme(bool valor);
};
//FichaTerreno

#define FichaPisoFirme 0
#define FichaPisoEnemigos 1
#define FichaPisoFondoLava 2
//Terminar de Programar a futuro
#define FichaPisoFondoPradera 2
#define FichaPisoFondoGelido 2
#define FichaPisoFondoDesierto 2


class FichaTerreno: public Ficha{
 private:
 protected:
 public:
  FichaTerreno(int x2, int y2, int id2, int tipo, VectorDeSprites &sprites);
  FichaTerreno(const FichaTerreno &p);
  void cambiarTipo(int tipo, VectorDeSprites &vectorDeSprites);
};

#define FichaTorreDeTierra 0
#define FichaTorreDeFuego 1
#define FichaTorreDeAire 2
#define FichaTorreDeAgua 3

class FichaTorre: public Ficha{
 private:
 protected:
  int danio;
  int rango;
  int especial;
  int spriteActualSubAnimacion;
 public:
  FichaTorre(int x2, int y2, int id2, int tipo, VectorDeSprites &sprites);
  FichaTorre(Communication::Tower actualzacion, VectorDeSprites &sprites);
  FichaTorre(const FichaTorre &p);
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& cr, DatosPantalla datosActuales);
  virtual void ejecutarSicloDeAnimacion(); //Para los gif
  int getDanio() const;
  int getRango() const;
  int getEspecial() const;
  void actualizar(Communication::Tower actualzacion);
};

#define Abmonible 0

#define masX 36;
#define masY 0;
#define menosX 12;
#define menosY 24;

class FichaEnemigo: public Ficha{
 private:
 protected:
 //para las voladoras.
  int correccionX;
  int correccionY;
  int inicioAnimiacionActual;
 public:
  //todo se puede intentar mejorar. Con una correccion de la posicion.
  FichaEnemigo(int x2, int y2, int id2, int tipo, VectorDeSprites &sprites);
  FichaEnemigo(Communication::Enemy actualzacion, VectorDeSprites &sprites);
  FichaEnemigo(const FichaEnemigo &p);
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& cr, DatosPantalla datosActuales);
  virtual void ejecutarSicloDeAnimacion(); //Para los gif
  void actualizar(Communication::Enemy actualzacion);
};

#define FichaPortalAzul 0
#define FichaPortalRojo 1

class FichaPortal: public Ficha{
 private:
 protected:
  int spriteActualSubAnimacion;
 public:
  FichaPortal(int x2, int y2, int id2, int tipo, VectorDeSprites &sprites);
  FichaPortal(const FichaPortal &p);
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& cr, DatosPantalla datosActuales);
  virtual void ejecutarSicloDeAnimacion(); //Para los gif
};

#define FichaGrieta 4
//valas. Poderes estatico y poderes a objetivos
class FichaEfectos: public Ficha{
 private:
 protected:
  int tiempoImpacto;
  FichaEnemigo *objetivo;
 public:
  FichaEfectos(FichaTorre &inicio, int id2, VectorDeSprites &sprites,
     FichaEnemigo &objetivo2);
  FichaEfectos(int x2, int y2, int id2, int tipo, VectorDeSprites &sprites);
  //FichaEfectos(int id2, int tipo, VectorDeSprites &sprites, FichaEnemigo *objetivo2);
  FichaEfectos(const FichaEfectos &p);
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& cr, DatosPantalla datosActuales);
  virtual void ejecutarSicloDeAnimacion(); //Para los gif
};

#endif
