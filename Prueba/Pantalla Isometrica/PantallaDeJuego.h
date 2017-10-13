#ifndef __FPANTALLAJUEGO_H__
#define __FPANTALLAJUEGO_H__
//cosa a mejorar
#include <gtkmm.h>
#include <iostream>
#include "sprites.h"
#include "Fichas.h"
#include "OrdenadorDeFichas.h"

class PantallaDeJuego: public Gtk::DrawingArea{
private:
  //tal vez un mapa no sea lo mejor.
 OrdenadorDeFichas &fichas;
 int width;
 int height;
 int desplasamientoX;
 int desplasamientoY;
  bool on_key_press_event(GdkEventKey* event) override;
protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override; //la verdad de la milaneza
public:
  PantallaDeJuego(OrdenadorDeFichas &fichas2);
  void pulsaion();
  virtual ~PantallaDeJuego();
};
#endif
