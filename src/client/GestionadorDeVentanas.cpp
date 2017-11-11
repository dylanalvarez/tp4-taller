#include "GestionadorDeVentanas.h"

GestionadorDeVentanas::GestionadorDeVentanas(
  Glib::RefPtr<Gtk::Builder> &ventana2,
    Glib::RefPtr<Gtk::Application> app2):app(app2){
    ventana2->get_widget("Juego", juego);
    ventana2->get_widget("ElegirElementos", pantallaDeElementos);
    ventana2->get_widget("creaccion", pantallaDeInicio);
  }


void GestionadorDeVentanas::arrancarJuego(){
  juego->show_all();
  app = Gtk::Application::create();
  app->run(*juego);
}

void GestionadorDeVentanas::TerminarJuego(){
  juego->hide();
}

void GestionadorDeVentanas::actualizar(
  const Communication::GameState &gameState){
  /*if (!elementosElegidos) {
    elementosElegidos = true;
    TerminarPantallaDeElementos
  }*/
  if (gameState.state !=Communication::GameState::State::ongoing) {
    TerminarJuego();
  }
}

void GestionadorDeVentanas::arrancarPantallaDeElementos(){
  if (!iniciado) 
    return
  pantallaDeElementos->show_all();
  app = Gtk::Application::create();
  app->run(*pantallaDeElementos);
}

void GestionadorDeVentanas::TerminarPantallaDeElementos(){
  pantallaDeElementos->hide();
}

void GestionadorDeVentanas::arrancarPantallaDeInicio(){
  pantallaDeInicio->show_all();
  app = Gtk::Application::create();
  app->run(*pantallaDeInicio);
}

void GestionadorDeVentanas::TerminarPantallaDeInicio(){
  pantallaDeInicio->hide();
  iniciado = true;
}
