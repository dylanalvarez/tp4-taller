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
#include "../common/Socket.h"
//esta clase es solo para dirigir el movimiento en este caso.

#define largo 88
#define teimpoActualizacionModelo 15

int main(int argc, char *argv[]){
  /*if (argc != 2) {
    return 0;
  }*/
  //char *servicename= argv[1];
  //Socket socket("127.0.0.1", servicename); //Algo raro pasa aca.
  Socket socket("127.0.0.1", "7072");

  //Crea la aplicación de gtkmm (Todo esto tendria que ser un un clase)
  auto app = Gtk::Application::create(argc, argv);
  VectorDeSprites sprites;
  OrdenadorDeFichas fichas;

//mapa Hercodado.
  int XpisosFirmos[] = {2,3,6,6,6,7,8,9};
  int YpisosFirmos[] = {3,3,3,4,5,8,8,8};
  int XpisosEnemigo[] = {44,44,132,132,220,220,308,308,396,396,396,396,396,396,
    396,484,484,572,572,660,660,748,748,836,836};
  int YpisosEnemigo[] = {132,132,132,132,132,132,132,132,132,132,220,308,396,484,
    572,572,572,572,572,572,572,572,572,572,572};

  int id = 0;
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      id++;
      fichas.agregarTerreno(FichaTerreno(largo*i, largo*j, id, FichaPisoFondoLava, sprites));
    }
  }
  for (size_t i = 0; i < 8; i++) {
    id = fichas.ObetenerTerrenoEnEstaPosicion((XpisosFirmos[i]-1)*88,(YpisosFirmos[i]-1)*88);
    fichas.getTerreno(id).cambiarTipo(FichaPisoFirme, sprites);
  }
  for (size_t i = 0; i < 24; i++) {
    id = fichas.ObetenerTerrenoEnEstaPosicion(XpisosEnemigo[i],YpisosEnemigo[i]);
    fichas.getTerreno(id).cambiarTipo(FichaPisoEnemigos, sprites);
  }

	Gtk::Window* window;
  Gtk::Box* Box;

	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	refBuilder->add_from_file("Sprites/Pantallas/Pantalla principal.glade");
  //creo pantalla
  Emisor emisor;
  PantallaDeJuego area (fichas, refBuilder, emisor);
  area.agregarElemento(tierra);

	refBuilder->get_widget("cajaJuego", Box);
  Box->pack_start(area);
	refBuilder->get_widget("applicationwindow1", window);
  window->show_all();


  GameClientReceiver reciver(fichas, area.getMenuTorres());
  GameClientSocket clientSocket(reciver, std::move(socket));
  Receptor receptor(reciver, clientSocket);
  ControladorDeSiclos falso(receptor, emisor);

//mejorar nombres
  int TiempoEnMilesegundos = 100;
  sigc::slot<bool> my_slot = sigc::mem_fun(area, &PantallaDeJuego::ejecutarSicloDeAnimacion);
  sigc::connection conn = Glib::signal_timeout().connect(my_slot,TiempoEnMilesegundos);
  TiempoEnMilesegundos = 50;
  sigc::slot<bool> my_slot2 = sigc::mem_fun(area, &PantallaDeJuego::ejecutarSicloDesplasamientos);
  sigc::connection conn2 = Glib::signal_timeout().connect(my_slot2,TiempoEnMilesegundos);

  /*TiempoEnMilesegundos = teimpoActualizacionModelo;
  sigc::slot<bool> my_slot3 = sigc::mem_fun(falso, &ControladorDeSiclos::continuar);
  sigc::connection conn3 = Glib::signal_timeout().connect(my_slot3,TiempoEnMilesegundos);
*/
  falso.iniciar();
  app->run(*window);
  falso.terminar();

  return 0;
}
