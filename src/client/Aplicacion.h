#include "PantallaDeJuego.h"
#include "controladorDeCiclos.h"
#include "PantallaResultado.h"
#include "../common/Exception.h"

class Aplicacion {
private:
    Glib::RefPtr<Gtk::Application> app;
    OrdenadorDeFichas fichas;
    Gtk::Box *Box;
    Glib::RefPtr<Gtk::Builder> refBuilder;
    Emisor emisor;
    PantallaDeJuego area;
    GestionadorDeVentanas ventanas;
    PantallaResultado victoria;
    PantallaResultado derrota;
    PantallaDeInicio pantallaInicial;
    PantallaDeElementos pantallaDeElementos;
    GameClientReceiver reciver;
    GameClientSocket clientSocket;
    Receptor receptor;
    controladorDeCiclos cdCiclos;
public:
  Aplicacion(Socket &&socket);

  
};
