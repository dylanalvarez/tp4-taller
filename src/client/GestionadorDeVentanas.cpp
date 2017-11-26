#include "GestionadorDeVentanas.h"


void GestionadorDeVentanas::arrancar() {
    while (volverAempezar) {
        pantalla_victoria->hide();
        pantalla_derrota->hide();
        volverAempezar = false;
        iniciado = false;
        elementosElegidos = false;
        juegoTerminado = false;
        arrancarPantallaDeInicio();
        arrancarPantallaDeElementos();
        arrancarJuego();
        arrancarPantallaResultado();
    }
}


GestionadorDeVentanas::GestionadorDeVentanas(
        Glib::RefPtr<Gtk::Builder> &ventana2,
        PantallaDeJuego &juego2): contoladorJuego(juego2) {
    ventana2->get_widget("Juego", juego);
    ventana2->get_widget("ElegirElementos", pantallaDeElementos);
    ventana2->get_widget("creaccion", pantallaDeInicio);
    ventana2->get_widget("creaccion", pantallaDeInicio);
    ventana2->get_widget("defeat", pantalla_derrota);
    ventana2->get_widget("victory", pantalla_victoria);
}


void GestionadorDeVentanas::arrancarJuego() {
    contoladorJuego.reniciarDesplasamiento();
    if (elementosElegidos) {
        juego->show_all();
        juego->maximize();
        app = Gtk::Application::create();
        app->run(*juego);
    }
}

void GestionadorDeVentanas::TerminarJuego() {
    juego->hide();
}

void GestionadorDeVentanas::actualizar(
        const Communication::GameState &gameState) {
    if (!elementosElegidos) {
        elementosElegidos = true;
        TerminarPantallaDeElementos();
    }
    if (gameState.state == Communication::GameState::State::lost) {
        TerminarJuego();
        juegoTerminado = true;
        gano = false;
    } else if (gameState.state == Communication::GameState::State::won) {
        TerminarJuego();
        juegoTerminado = true;
        gano = true;
    }
}

void GestionadorDeVentanas::arrancarPantallaDeElementos() {
    if (iniciado) {
        pantallaDeElementos->show_all();
        app = Gtk::Application::create();
        app->run(*pantallaDeElementos);
    }
}

void GestionadorDeVentanas::TerminarPantallaDeElementos() {
    pantallaDeElementos->hide();
}

void GestionadorDeVentanas::arrancarPantallaDeInicio() {
    pantallaDeInicio->show_all();
    app = Gtk::Application::create();
    app->run(*pantallaDeInicio);
}

void GestionadorDeVentanas::TerminarPantallaDeInicio() {
    pantallaDeInicio->hide();
    iniciado = true;
}

void GestionadorDeVentanas::GanarJuego() {
    juego->hide();
}

void GestionadorDeVentanas::arrancarPantallaResultado() {
    if (juegoTerminado) {
        if (gano) {
            pantalla_victoria->show_all();
            app = Gtk::Application::create();
            app->run(*pantalla_victoria);
        } else {
            pantalla_derrota->show_all();
            app = Gtk::Application::create();
            app->run(*pantalla_derrota);
        }
    }
}

void GestionadorDeVentanas::TerminarPantallaResultado() {
    pantalla_derrota->hide();
    pantalla_victoria->hide();
    volverAempezar = true;
}
