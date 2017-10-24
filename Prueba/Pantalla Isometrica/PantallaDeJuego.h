#ifndef __FPANTALLAJUEGO_H__
#define __FPANTALLAJUEGO_H__
//cosa a mejorar
#include <gtkmm.h>
#include <iostream>
#include "sprites.h"
#include "Fichas.h"
#include "OrdenadorDeFichas.h"
#include "menuTorres.h"


class PantallaDeJuego: public Gtk::DrawingArea{
private:
  //tal vez un mapa no sea lo mejor.
 OrdenadorDeFichas &fichas;
 MenuTorres menuTorres;
 int width;
 int height;
 int desplasamientoX;
 int desplasamientoY;
 bool incirementeEnX;
 bool decrementoEnX;
 bool incirementeEnY;
 bool decrementoEnY;
  bool on_key_press_event(GdkEventKey* event) override;
  bool on_button_press_event(GdkEventButton* event) override;
  bool on_motion_notify_event(GdkEventMotion* event) override;
  bool on_leave_notify_event (GdkEventCrossing* event) override;
  void desplasamientoIncirementeEnX();
  void desplasamientoDecrementoEnX();
  void desplasamientoIncirementeEnY();
  void desplasamientoDecrementoEnY();
protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override; //la verdad de la milaneza
public:
  PantallaDeJuego(OrdenadorDeFichas &fichas2, Glib::RefPtr<Gtk::Builder> &ventana);
  bool ejecutarSicloDeAnimacion();
  bool ejecutarSicloDesplasamientos();
  virtual ~PantallaDeJuego();
};
#endif
