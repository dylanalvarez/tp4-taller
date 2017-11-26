#ifndef __PPINICIO_H__
#define __PPINICIO_H__

#include <gtkmm.h>
#include <iostream>
#include "Fichas.h"
#include "TiposDeDatosExpeciales.h"
#include "Menu.h"
#include "emisor.h"
#include <string>
#include <map>

class PantallaDeInicio {
private:
    Emisor &emisorComandos;
    Menu &menu;
    Gtk::Button *unirse;
    Gtk::Button *crear;
    Gtk::Entry *nick;
    Gtk::Entry *nickEquipo;
    Gtk::ComboBoxText *equipos;
    Gtk::ComboBoxText *mapas;
    std::map<std::string, int> ids;
protected:
public:
    void unirsePartida();

    void crearPartida();

    PantallaDeInicio(Glib::RefPtr<Gtk::Builder> &ventana, Emisor &emisor,
                     Menu &menu2);

    void cargarDatos(
            const std::vector<Communication::NameAndID> &matches,
            const std::vector<Communication::NameAndID> &maps);
};

#endif
