#ifndef __FFICHAS_H__
#define __FFICHAS_H__

#include <gtkmm.h>
#include <iostream>
#include "sprites.h"
#include "VectorDeSprites.h"
#include "TiposDeDatosExpeciales.h"


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
  virtual void ejecutarCicloDeAnimacion(); //Para los gif
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
#define FichaPisoFondoPradera 3
#define FichaPisoFondoGelido 4
#define FichaPisoFondoDesierto 5

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
  virtual void ejecutarCicloDeAnimacion();
  int getDanio() const;
  int getRango() const;
  int getEspecial() const;
  void actualizar(Communication::Tower actualzacion);
};

#define Abmonible 0
#define DemonioVerde 1
#define HalconSangriento 2
#define Espectro 3
#define HombreCabra 4
#define NoMuerto 5

#define masX 3;
#define masY 0;
#define menosX 1;
#define menosY 2;

class FichaEnemigo: public Ficha{
 private:
 protected:
  int correccionX;
  int correccionY;
  int inicioAnimiacionActual;
  int largoAnimiacionActual;
 public:
  //todo se puede intentar mejorar. Con una correccion de la posicion.
  FichaEnemigo(int x2, int y2, int id2, int tipo, VectorDeSprites &sprites);
  FichaEnemigo(Communication::Enemy actualzacion, VectorDeSprites &sprites);
  FichaEnemigo(const FichaEnemigo &p);
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& cr, DatosPantalla datosActuales);
  virtual void ejecutarCicloDeAnimacion(); //Para los gif
  void actualizar(Communication::Enemy actualzacion);
};

#define FichaPortalAzul1 0
#define FichaPortalRojo1 1
#define FichaPortalAzul2 3
#define FichaPortalRojo2 4

class FichaPortal: public Ficha{
 private:
 protected:
  int spriteActualSubAnimacion;
  int largoAnimiacionActual;
 public:
  FichaPortal(int x2, int y2, int id2, int tipo, VectorDeSprites &sprites);
  FichaPortal(const FichaPortal &p);
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& cr, DatosPantalla datosActuales);
  virtual void ejecutarCicloDeAnimacion(); //Para los gif
};


#define FichaAtaqueTierra 0
#define FichaAtaqueFuego 1
#define FichaAtaqueAire 2
#define FichaAtaqueAgua 3
//las primeras 4 tienen que ser igual a las torres.
#define FichaCongelacion 4
#define FichaRayos 5
//de 0 a 5 es tarjetado
#define FichaGrieta 6
#define FichaMetorito 7
#define FichaTornado 8
#define FichaVentisca 9
#define FichafireWall 10
#define FichaPing 11
//valas. Poderes estatico y poderes a objetivos

class FichaEfectos: public Ficha{
 private:
 protected:
  int tiempoImpacto;
  FichaEnemigo *objetivo;
  int largoAnimiacionActual;
 public:
  FichaEfectos(FichaTorre &inicio, int id2, VectorDeSprites &sprites,
     FichaEnemigo &objetivo2);
  FichaEfectos(int id2, int tipo, VectorDeSprites &sprites,
     FichaEnemigo &objetivo2);
  FichaEfectos(int x2, int y2, int id2, int tipo, VectorDeSprites &sprites);
  FichaEfectos(const FichaEfectos &p);
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& cr, DatosPantalla datosActuales);
  virtual void ejecutarCicloDeAnimacion(); //Para los gif
  void ejecutarcicloDeActualizacion();
};

#endif
