#ifndef __PPELEMENTOS_H__
#define __PPELEMENTOS_H__

#include <gtkmm.h>
#include <iostream>
#include "Fichas.h"
#include "TiposDeDatosExpeciales.h"
#include "emisor.h"
#include <string>

class PantallaDeElementos{
 private:
	Emisor& emisorComandos;
  Gtk::ToggleButton* botonFuego;
  Gtk::ToggleButton* botonTierra;
  Gtk::ToggleButton* botonAgua;
  Gtk::ToggleButton* botonAire;
  Gtk::Button* listo;
  Gtk::Button* elegir;
  Gtk::Label* error;
 protected:
 public:
  PantallaDeElementos(Glib::RefPtr<Gtk::Builder> &ventana, Emisor& emisor);
  void elementoSeleccionado(Elementos elemento);
  void clikearFuego();
  void clikearTierra();
  void clikearAgua();
  void clikearAire();
  void clikearListo();
  void clikearElegir();
};

#endif
