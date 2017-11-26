#include "Aplicacion.h"


Aplicacion::Aplicacion(Socket &&socket, Glib::RefPtr<Gtk::Builder> &refBuilder):
area(fichas, refBuilder, emisor),
ventanas(refBuilder,area),
victoria(refBuilder, "victory", ventanas),
derrota(refBuilder, "defeat", ventanas),
pantallaInicial(refBuilder, emisor, area.getMenu()),
pantallaDeElementos(refBuilder, emisor),
reciver(fichas, area.getMenu(), ventanas, pantallaInicial, pantallaDeElementos),
clientSocket(reciver, std::move(socket)), receptor(reciver, clientSocket),
cdCiclos(receptor, emisor){
  refBuilder->get_widget("cajaJuego", Box);
  Box->pack_start(area);
  emisor.cargarSocket(&clientSocket);
}

bool Aplicacion::ejecutarCicloDeAnimacion(){
  return area.ejecutarCicloDeAnimacion();
}


bool Aplicacion::ejecutarcicloDesplasamientos(){
  return area.ejecutarcicloDesplasamientos();
}


void Aplicacion::arrancar(){
  cdCiclos.iniciar();
  ventanas.arrancar();
  cdCiclos.terminar();
}
