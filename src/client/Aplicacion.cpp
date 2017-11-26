#include "Aplicacion.h"


Aplicacion::Aplicacion(Socket &&socket): app(Gtk::Application::create()),
refBuilder(Gtk::Builder::create()), area(fichas, refBuilder, emisor),
ventanas(refBuilder,area),
victoria(refBuilder, "victory", ventanas),
derrota(refBuilder, "defeat", ventanas),
pantallaInicial(refBuilder, emisor, area.getMenu()),
pantallaDeElementos(refBuilder, emisor),
reciver(fichas, area.getMenu(), ventanas, pantallaInicial, pantallaDeElementos),
clientSocket(reciver, std::move(socket)), receptor(reciver, clientSocket),
cdCiclos(receptor, emisor){
  refBuilder->add_from_file("Sprites/Pantallas/Pantalla principal.glade");
  refBuilder->get_widget("cajaJuego", Box);
  Box->pack_start(area);
  emisor.cargarSocket(&clientSocket);
}
