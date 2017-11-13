#include "GestionadorDeVentanas.h"

GestionadorDeVentanas::GestionadorDeVentanas(
  Glib::RefPtr<Gtk::Builder> &ventana2){
    ventana2->get_widget("Juego", juego);
    ventana2->get_widget("ElegirElementos", pantallaDeElementos);
    ventana2->get_widget("creaccion", pantallaDeInicio);
    ventana2->get_widget("creaccion", pantallaDeInicio);
    ventana2->get_widget("defeat", pantalla_derrota);
    ventana2->get_widget("victory", pantalla_victoria);
  }


void GestionadorDeVentanas::arrancarJuego(){
  if (elementosElegidos){
    juego->show_all();
    app = Gtk::Application::create();
    app->run(*juego);
  }  
}

void GestionadorDeVentanas::TerminarJuego(){
  juego->hide();
  pantalla_derrota->show_all();
  app = Gtk::Application::create();
  app->run(*pantalla_derrota);
}

void GestionadorDeVentanas::actualizar(
  const Communication::GameState &gameState){
  if (!elementosElegidos) {
    elementosElegidos = true;
    TerminarPantallaDeElementos();
  }
  if (gameState.state == Communication::GameState::State::lost) {
    TerminarJuego();
  } else if (gameState.state == Communication::GameState::State::won) {
      GanarJuego();
  }
}

void GestionadorDeVentanas::arrancarPantallaDeElementos(){
  if (iniciado){
    pantallaDeElementos->show_all();
    app = Gtk::Application::create();
    app->run(*pantallaDeElementos);
  }
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

void GestionadorDeVentanas::GanarJuego() {
  juego->hide();
  pantalla_victoria->show_all();
  app = Gtk::Application::create();
  app->run(*pantalla_victoria);
}
