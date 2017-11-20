#include "PantallaDeElementos.h"


PantallaDeElementos::PantallaDeElementos (Glib::RefPtr<Gtk::Builder> &ventana, Emisor& emisor):
                  emisorComandos(emisor){
  	ventana->get_widget("fuego2", botonFuego);
  	ventana->get_widget("tierra2", botonTierra);
  	ventana->get_widget("agua2", botonAgua);
  	ventana->get_widget("aire2", botonAire);
  	ventana->get_widget("listo", listo);
  	ventana->get_widget("elegir", elegir);
  	ventana->get_widget("ErrorElementos", error);

    listo->signal_clicked().connect(
      sigc::mem_fun(this, &PantallaDeElementos::clikearListo));
    elegir->signal_clicked().connect(
      sigc::mem_fun(this, &PantallaDeElementos::clikearElegir));

    botonFuego->signal_toggled().connect(
      sigc::mem_fun(this, &PantallaDeElementos::clikearFuego));
    botonTierra->signal_toggled().connect(
      sigc::mem_fun(this, &PantallaDeElementos::clikearTierra));
    botonAgua->signal_toggled().connect(
      sigc::mem_fun(this, &PantallaDeElementos::clikearAgua));
    botonAire->signal_toggled().connect(
      sigc::mem_fun(this, &PantallaDeElementos::clikearAire));
  }

void PantallaDeElementos::clikearFuego(){
 }
void PantallaDeElementos::clikearTierra(){
 }
void PantallaDeElementos::clikearAgua(){
 }
void PantallaDeElementos::clikearAire(){
 }
void PantallaDeElementos::clikearListo(){
  emisorComandos.empesarJuego();
}
void PantallaDeElementos::clikearElegir(){
  if (botonFuego->get_active())
    emisorComandos.elegirElemento("fire");
  if (botonTierra->get_active())
    emisorComandos.elegirElemento("earth");
  if (botonAgua->get_active())
    emisorComandos.elegirElemento("water");
  if (botonAire->get_active())
    emisorComandos.elegirElemento("air");
}


void PantallaDeElementos::reiniciar(){
  botonTierra->set_sensitive(true);
  botonAgua->set_sensitive(true);
  botonFuego->set_sensitive(true);
  botonAire->set_sensitive(true);
}
void PantallaDeElementos::elementoSeleccionado(Elementos elemento){
  switch (elemento) {
    case tierra:
      botonTierra->set_active(false);
      botonTierra->set_sensitive(false);
      break;
    case agua:
      botonAgua->set_active(false);
      botonAgua->set_sensitive(false);
      break;
    case fuego:
      botonFuego->set_active(false);
      botonFuego->set_sensitive(false);
      break;
    case aire:
      botonAire->set_active(false);
      botonAire->set_sensitive(false);
  }
}
