//
// Created by facundo on 13/11/17.
//

#include "PantallaResultado.h"

PantallaResultado::PantallaResultado(Glib::RefPtr<Gtk::Builder> &ventana,
                                     const std::string& window_name,
                                     GestionadorDeVentanas& Ventanas2):
                                     ventanas(Ventanas2) {
    ventana->get_widget(window_name + "_btn_ok", btn_ok);
    ventana->get_widget(window_name, this_window);
    btn_ok->signal_clicked().connect(
            sigc::mem_fun(this, &PantallaResultado::on_ok_clicked));
}

void PantallaResultado::on_ok_clicked() {
    this_window->hide();
    ventanas.TerminarPantallaResultado();
}
