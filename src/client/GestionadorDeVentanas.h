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
  bool iniciado = false;
  bool elementosElegidos = false;
  //Gtk::Window* pantallaFinal;
 protected:
 public:
   //los arrancar se ejecutan en el Hilo principal. y el terminar en otro hilo
   GestionadorDeVentanas(Glib::RefPtr<Gtk::Builder> &ventana2,
     Glib::RefPtr<Gtk::Application> app2);
   void arrancar();
   void arrancarJuego();
   void TerminarJuego();
   void actualizar(const Communication::GameState &gameState);
   void arrancarPantallaDeElementos();
   void TerminarPantallaDeElementos();
   void arrancarPantallaDeInicio();
   void TerminarPantallaDeInicio();
};



#endif
