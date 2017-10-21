#include "menuTorres.h"


MenuTorres::MenuTorres (Glib::RefPtr<Gtk::Builder> &ventana2): ventana(ventana2){
  	ventana->get_widget("NombreTorre", titulo);
  	ventana->get_widget("Datos1", rango);
    ventana->get_widget("Upgred1", upgradeRango);
    ventana->get_widget("Datos2", danio);
    ventana->get_widget("Upgred2", upgradeDanio);
    ventana->get_widget("Datos3", especial);
    ventana->get_widget("Upgred3", upgradeEspecial);
}
void MenuTorres::cargarTorre (const FichaTorre &torre2){
  torre =  &torre2;
  switch (torre->getTipo()) {
    case FichaTorreDeTierra:
      titulo->set_text("Torre De Tierra");
      break;
    case FichaTorreDeFuego:
      titulo->set_text("Torre De Fuego");
      break;
    case FichaTorreDeAire:
      titulo->set_text("Torre De Aire");
      break;
    case FichaTorreDeAgua:
      titulo->set_text("Torre De Agua");
      break;
    default:
      break;
  }
}
