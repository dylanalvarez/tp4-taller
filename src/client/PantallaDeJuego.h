#ifndef __FPANTALLAJUEGO_H__
#define __FPANTALLAJUEGO_H__
//cosa a mejorar
#include <gtkmm.h>
#include <iostream>
#include "sprites.h"
#include "Fichas.h"
#include "OrdenadorDeFichas.h"
#include "Menu.h"
#include "TiposDeDatosExpeciales.h"
#include "emisor.h"


class PantallaDeJuego : public Gtk::DrawingArea {
public:
    PantallaDeJuego(OrdenadorDeFichas &fichas2,
                    Glib::RefPtr<Gtk::Builder> &ventana,
                    Emisor &emisor);

    bool ejecutarCicloDeAnimacion();

    bool ejecutarcicloDesplasamientos();

    void agregarElemento(Elementos elemento);

    virtual ~PantallaDeJuego();

    Menu &getMenu();

protected:
    std::vector<Elementos> elementos;
    OrdenadorDeFichas &fichas;
    Menu menu;
    DatosPantalla datosActuales;
    bool incirementeEnX;
    bool decrementoEnX;
    bool incirementeEnY;
    bool decrementoEnY;

    bool on_key_press_event(GdkEventKey *event) override;

    bool on_button_press_event(GdkEventButton *event) override;

    bool on_motion_notify_event(GdkEventMotion *event) override;

    bool on_leave_notify_event(GdkEventCrossing *event) override;

    void desplazamientoIncrementalEnX();

    void desplazamientoDecrementalEnX();

    void desplazamientoIncrementalEnY();

    void desplazamientoDecrementalEnY();

    bool
    on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override; //la verdad de la milaneza
};

#endif
