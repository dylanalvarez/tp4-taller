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
#include "PantallaResultado.h"
//esta clase es solo para dirigir el movimiento en este caso.

#define largo 88
#define teimpoActualizacionModelo 15

int main(int argc, char *argv[]){
  if (argc != 2) {
    return 0;
  }
  Socket socket("127.0.0.1", argv[1]); //Algo raro pasa aca.

  //esto.. no estamos de todo seguro.
  int argcF =argc -1;
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argcF, argv);


  OrdenadorDeFichas fichas;
  Gtk::Box* Box;
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	refBuilder->add_from_file("Sprites/Pantallas/Pantalla principal.glade");
  //creo objetos
  Emisor emisor;
  PantallaDeJuego area (fichas, refBuilder, emisor);
	refBuilder->get_widget("cajaJuego", Box);
  Box->pack_start(area);
  GestionadorDeVentanas ventanas(refBuilder);
  PantallaResultado victoria(refBuilder, "victory");
  PantallaResultado derrota(refBuilder, "defeat");
  PantallaDeInicio pantallaInicial(refBuilder, emisor, area.getMenuTorres());
  PantallaDeElementos pantallaDeElementos(refBuilder, emisor);
  GameClientReceiver reciver(fichas, area.getMenuTorres(),
   ventanas, pantallaInicial,pantallaDeElementos);
  GameClientSocket clientSocket(reciver, std::move(socket));
  Receptor receptor(reciver, clientSocket);
  ControladorDeSiclos controladorDeSiclos(receptor, emisor);
  emisor.cargarSocket(&clientSocket);

//pongo Timers
  int TiempoEnMilesegundos = 100;
  sigc::slot<bool> my_slot = sigc::mem_fun(area, &PantallaDeJuego::ejecutarSicloDeAnimacion);
  sigc::connection conn = Glib::signal_timeout().connect(my_slot,TiempoEnMilesegundos);
  TiempoEnMilesegundos = 50;
  sigc::slot<bool> my_slot2 = sigc::mem_fun(area, &PantallaDeJuego::ejecutarSicloDesplasamientos);
  sigc::connection conn2 = Glib::signal_timeout().connect(my_slot2,TiempoEnMilesegundos);

  //arranco

  controladorDeSiclos.iniciar();
  ventanas.arrancarPantallaDeInicio();
  ventanas.arrancarPantallaDeElementos();
  ventanas.arrancarJuego();
  ventanas.arrancarPantallaResultado();
  controladorDeSiclos.terminar();

  return 0;
}
