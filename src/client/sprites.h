#ifndef __FSPRITES_H__
#define __FSPRITES_H__
//cosa a mejorar
#include <gtkmm.h>
#include <iostream>
#include <list>
#include "TiposDeDatosExpeciales.h"

class Sprite{
protected:
  Glib::RefPtr<Gdk::Pixbuf> &image; //cosa a mejorar
  int x;
  int y;
public:
  Sprite(int x2, int y2, Glib::RefPtr<Gdk::Pixbuf>& image2);
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& cr);
  virtual void dibujarIsometrico(const Cairo::RefPtr<Cairo::Context>& cr, DatosPantalla datosActuales);
  void cambiarPosicion(int x2, int y2);
  int obtenerAlto();
  int obtenerHancho();
  virtual ~Sprite();
};
#endif
