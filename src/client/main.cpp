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
#include "GestionadorDeVentanas.h"
#include "PantallaDeInicio.h"
#include "PantallaDeElementos.h"
#include "../common/Socket.h"
//esta clase es solo para dirigir el movimiento en este caso.

#define largo 88
#define teimpoActualizacionModelo 15

int main(int argc, char *argv[]){
  if (argc != 2) {
    return 0;
  }
  //char *servicename= argv[1];
  Socket socket("127.0.0.1", argv[1]); //Algo raro pasa aca.
  //Socket socket("127.0.0.1", "7072");
  int argcF =argc -1;
  //Crea la aplicación de gtkmm (Todo esto tendria que ser un un clase)
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argcF, argv);
  VectorDeSprites sprites;
  OrdenadorDeFichas fichas;

//mapa Hercodado.
  int XpisosFirmos[] = {2,3,6,6,6,7,8,9};
  int YpisosFirmos[] = {3,3,3,4,5,8,8,8};
  int XpisosEnemigo[] = {1,2,3,4,4,4,4,4,4,5,6,7,8,9,10};
  int YpisosEnemigo[] = {1,1,1,1,2,3,4,5,6,6,6,6,6,6,6};

  int id = 0;
  for (size_t i = 1; i < 11; i++) {
    for (size_t j = 1; j < 11; j++) {
      id++;
      fichas.agregarTerreno(FichaTerreno(largo*i-44, largo*j-44, id, FichaPisoFondoLava, sprites));
    }
  }
  for (size_t i = 0; i < 8; i++) {
    id = fichas.ObetenerTerrenoEnEstaPosicion((XpisosFirmos[i])*88-44,(YpisosFirmos[i])*88-44);
    fichas.getTerreno(id).cambiarTipo(FichaPisoFirme, sprites);
  }
  for (size_t i = 0; i < 15; i++) {
    id = fichas.ObetenerTerrenoEnEstaPosicion((XpisosEnemigo[i])*88-44,(YpisosEnemigo[i])*88-44);
    fichas.getTerreno(id).cambiarTipo(FichaPisoEnemigos, sprites);
  }

  Gtk::Box* Box;

	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	refBuilder->add_from_file("Sprites/Pantallas/Pantalla principal.glade");
  //creo pantalla
  Emisor emisor;
  PantallaDeJuego area (fichas, refBuilder, emisor);
  area.agregarElemento(tierra);

	refBuilder->get_widget("cajaJuego", Box);
  Box->pack_start(area);
  GestionadorDeVentanas ventanas(refBuilder, app);

  PantallaDeInicio pantallaInicial(refBuilder, emisor);
  PantallaDeElementos pantallaDeElementos(refBuilder, emisor);
  GameClientReceiver reciver(fichas, area.getMenuTorres(),
   ventanas, pantallaInicial,pantallaDeElementos);
  GameClientSocket clientSocket(reciver, std::move(socket));
  Receptor receptor(reciver, clientSocket);
  ControladorDeSiclos falso(receptor, emisor);
  emisor.cargarSocket(&clientSocket);

//mejorar nombres
  int TiempoEnMilesegundos = 100;
  sigc::slot<bool> my_slot = sigc::mem_fun(area, &PantallaDeJuego::ejecutarSicloDeAnimacion);
  sigc::connection conn = Glib::signal_timeout().connect(my_slot,TiempoEnMilesegundos);
  TiempoEnMilesegundos = 50;
  sigc::slot<bool> my_slot2 = sigc::mem_fun(area, &PantallaDeJuego::ejecutarSicloDesplasamientos);
  sigc::connection conn2 = Glib::signal_timeout().connect(my_slot2,TiempoEnMilesegundos);


  falso.iniciar();
  ventanas.arrancarPantallaDeInicio();
  ventanas.arrancarPantallaDeElementos();
  ventanas.arrancarJuego();
  falso.terminar();

  return 0;
}
