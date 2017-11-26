#ifndef TOWERDEFENSE_PANTALLARESULTADO_H
#define TOWERDEFENSE_PANTALLARESULTADO_H


#include <gtkmm/button.h>
#include "../editor/Builder.h"
#include "GestionadorDeVentanas.h"

class PantallaResultado {
public:
    PantallaResultado(Glib::RefPtr<Gtk::Builder> &ventana,
                      const std::string &window_name,
                      GestionadorDeVentanas &Ventanas2);

private:
    Gtk::Button *btn_ok;
    Gtk::Window *this_window;
    GestionadorDeVentanas &ventanas;

    void on_ok_clicked();
};


#endif //TOWERDEFENSE_PANTALLARESULTADO_H
