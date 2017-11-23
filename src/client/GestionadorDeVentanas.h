#ifndef __GDVENTANAS_H__
#define __GDVENTANAS_H__

#include <gtkmm.h>
#include <iostream>
#include "TiposDeDatosExpeciales.h"

class GestionadorDeVentanas{
 private:
  Glib::RefPtr<Gtk::Application> app;
  Gtk::Window* juego;
  Gtk::Window* pantallaDeElementos;
  Gtk::Window* pantallaDeInicio;
  Gtk::Window* pantalla_derrota;
  Gtk::Window* pantalla_victoria;
  bool iniciado = false;
  bool elementosElegidos = false;
  bool juegoTerminado = false;
  bool gano = false;
  bool volverAempezar = true;
  void arrancarPantallaDeInicio();
  void arrancarPantallaDeElementos();
  void arrancarJuego();
  void arrancarPantallaResultado();
 public:
   //los arrancar se ejecutan en el Hilo principal. y el terminar en otro hilo
   GestionadorDeVentanas(Glib::RefPtr<Gtk::Builder> &ventana2);
   void arrancar();
   void TerminarJuego();
   void GanarJuego();
   void actualizar(const Communication::GameState &gameState);
   void TerminarPantallaDeElementos();
   void TerminarPantallaDeInicio();
   void TerminarPantallaResultado();
};



#endif
