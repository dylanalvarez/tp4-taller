//Se incluyen todos los tipos de la librería (no óptimo)
#include <gtkmm.h>
#include <iostream>
#include <thread>
#include "PantallaDeJuego.h"
#include "controladorDeCiclos.h"
#include "PantallaResultado.h"
#include "../common/Exception.h"
#include "Aplicacion.h"

//esta clase es solo para dirigir el movimiento en este caso.

#define largo 88
#define teimpoActualizacionModelo 15

int main(int argc, char *argv[]) {
    if (argc < 2) { throw Exception("Invalid arguments (port needed)"); }
    Socket socket(argc == 2 ? "127.0.0.1" : argv[1],
                  argv[argc == 2 ? 1 : 2]);


    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create();
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
    refBuilder->add_from_file("../Resources/Sprites/Pantallas/Pantalla principal.glade");
    Aplicacion aplicacion(std::move(socket), refBuilder);

    unsigned int TiempoEnMilesegundos = 100;
    sigc::slot<bool> my_slot = sigc::mem_fun(aplicacion,
                                             &Aplicacion::ejecutarCicloDeAnimacion);
    sigc::connection conn = Glib::signal_timeout().connect(my_slot,
                                                           TiempoEnMilesegundos);
    TiempoEnMilesegundos = 50;
    sigc::slot<bool> my_slot2 = sigc::mem_fun(aplicacion,
                                              &Aplicacion::ejecutarcicloDesplasamientos);
    sigc::connection conn2 = Glib::signal_timeout().connect(my_slot2,
                                                            TiempoEnMilesegundos);
    aplicacion.arrancar();

    /*Glib::RefPtr<Gtk::Application> app = Gtk::Application::create();

    OrdenadorDeFichas fichas;
    Gtk::Box *Box;
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
    refBuilder->add_from_file("Sprites/Pantallas/Pantalla principal.glade");
    //creo objetos
    Emisor emisor;
    PantallaDeJuego area(fichas, refBuilder, emisor);
    refBuilder->get_widget("cajaJuego", Box);
    Box->pack_start(area);
    GestionadorDeVentanas ventanas(refBuilder,area);
    PantallaResultado victoria(refBuilder, "victory", ventanas);
    PantallaResultado derrota(refBuilder, "defeat", ventanas);
    PantallaDeInicio pantallaInicial(refBuilder, emisor, area.getMenu());
    PantallaDeElementos pantallaDeElementos(refBuilder, emisor);
    GameClientReceiver reciver(fichas, area.getMenu(),
                               ventanas, pantallaInicial, pantallaDeElementos);
    GameClientSocket clientSocket(reciver, std::move(socket));
    Receptor receptor(reciver, clientSocket);
    controladorDeCiclos controladorDeCiclos(receptor, emisor);
    emisor.cargarSocket(&clientSocket);

//pongo Timers
    unsigned int TiempoEnMilesegundos = 100;
    sigc::slot<bool> my_slot = sigc::mem_fun(area,
                                             &PantallaDeJuego::ejecutarCicloDeAnimacion);
    sigc::connection conn = Glib::signal_timeout().connect(my_slot,
                                                           TiempoEnMilesegundos);
    TiempoEnMilesegundos = 50;
    sigc::slot<bool> my_slot2 = sigc::mem_fun(area,
                                              &PantallaDeJuego::ejecutarcicloDesplasamientos);
    sigc::connection conn2 = Glib::signal_timeout().connect(my_slot2,
                                                            TiempoEnMilesegundos);

    //arranco

    controladorDeCiclos.iniciar();
    ventanas.arrancar();
    controladorDeCiclos.terminar();*/

    return 0;
}
