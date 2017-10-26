//Se incluyen todos los tipos de la librería (no óptimo)
#include <gtkmm.h>
#include <iostream>
#include <thread>
#include "PantallaDeJuego.h"
#include "VectorDeSprites.h"
#include "Fichas.h"
#include "OrdenadorDeFichas.h"
#include "controladorDeSiclos.h"
#include "menuTorres.h"
#include "TiposDeDatosExpeciales.h"

//esta clase es solo para dirigir el movimiento en este caso.

#define largo 88
int main(int argc, char *argv[])
{
  //Crea la aplicación de gtkmm
  auto app = Gtk::Application::create(argc, argv);
  VectorDeSprites sprites;
  OrdenadorDeFichas fichas;
  int id = 0;
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      fichas.agregarTerreno(FichaTerreno(largo*i, largo*j, id, FichaPisoFirme, sprites));
      id++;
    }
  }
  fichas.agregarTorre(FichaTorre(largo*5, largo*3, id, FichaTorreDeTierra, sprites));
  id++;
  fichas.agregarTorre(FichaTorre(largo*6, largo*3, id, FichaTorreDeTierra, sprites));
  id++;
  fichas.agregarTorre(FichaTorre(largo*7, largo*3, id, FichaTorreDeFuego, sprites));
  id++;
  fichas.agregarTorre(FichaTorre(largo*7, largo*7, id, FichaTorreDeAire, sprites));
  id++;
  fichas.agregarTorre(FichaTorre(largo*1, largo*8, id, FichaTorreDeAgua, sprites));
  id++;
  fichas.agregarEnemigo(FichaEnemigo(largo*2, largo*2, id, Abmonible, sprites));

  fichas.agregarPortal(FichaPortal(largo*0, largo*0, 0, FichaPortalAzul, sprites));

	Gtk::Window* window;
  Gtk::Box* Box;

	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	refBuilder->add_from_file("Sprites/Pantallas/Pantalla principal.glade");
  //creo pantalla
  PantallaDeJuego area (fichas, refBuilder);
  area.agregarElemento(tierra);

	refBuilder->get_widget("cajaJuego", Box);
  Box->pack_start(area);
	refBuilder->get_widget("applicationwindow1", window);
  window->show_all();

//mejorar nombres
  int TiempoEnMilesegundos = 100;
  sigc::slot<bool> my_slot = sigc::mem_fun(area, &PantallaDeJuego::ejecutarSicloDeAnimacion);
  sigc::connection conn = Glib::signal_timeout().connect(my_slot,TiempoEnMilesegundos);
  TiempoEnMilesegundos = 50;
  sigc::slot<bool> my_slot2 = sigc::mem_fun(area, &PantallaDeJuego::ejecutarSicloDesplasamientos);
  sigc::connection conn2 = Glib::signal_timeout().connect(my_slot2,TiempoEnMilesegundos);

  app->run(*window);
  return 0;
}
