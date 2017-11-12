#ifndef __PPINICIO_H__
#define __PPINICIO_H__

#include <gtkmm.h>
#include <iostream>
#include "Fichas.h"
#include "TiposDeDatosExpeciales.h"
#include "menuTorres.h"
#include "emisor.h"
#include <string>

class PantallaDeInicio{
 private:
	Emisor& emisorComandos;
  MenuTorres& menu;  
  Gtk::Button* unirse;
  Gtk::Button* crear;
  Gtk::Entry* nick;
  Gtk::Entry* nickEquipo;
  Gtk::ComboBoxText* equipos;
  Gtk::ComboBoxText* mapas;
 protected:
 public:
  void unirsePartida();
  void crearPartida();
  PantallaDeInicio(Glib::RefPtr<Gtk::Builder> &ventana, Emisor& emisor,
     MenuTorres& menu2);
  void cargarDatos(
          const std::vector<Communication::NameAndID> &matches,
          const std::vector<Communication::NameAndID> &maps);
};

#endif
