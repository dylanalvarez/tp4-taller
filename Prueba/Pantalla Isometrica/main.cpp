//Se incluyen todos los tipos de la librería (no óptimo)
#include <gtkmm.h>
#include <iostream>
#include "PantallaDeJuego.h"
#include "VectorDeSprites.h"
#include "Fichas.h"
#include "OrdenadorDeFichas.h"
//esta clase es solo para dirigir el movimiento en este caso.

#define largo 88

int main(int argc, char *argv[])
{
  //Crea la aplicación de gtkmm
  auto app = Gtk::Application::create(argc, argv);
  //Gtk::Window ventana;
  //ventana.set_default_size(1000, 1000);
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
  //creo pantalla
  PantallaDeJuego area (fichas);

  //creo boton
  /*Gtk::Button pulso("Pulsasion");
  pulso.signal_clicked().connect( sigc::mem_fun(
        area, &PantallaDeJuego::pulsaion) );

  Gtk::Box m_box1;
  m_box1.pack_start(pulso);
  m_box1.pack_start(area);
  ventana.add(m_box1);
  ventana.show_all();
*/
	Gtk::Window* window;
  Gtk::Box* Box;

	auto refBuilder = Gtk::Builder::create();
	refBuilder->add_from_file("Sprites/Pantallas/Pantalla principal.glade");

	refBuilder->get_widget("cajaJuego", Box);
  Box->pack_start(area);
	refBuilder->get_widget("applicationwindow1", window);
  window->show_all();
  app->run(*window);

  return 0;
}
