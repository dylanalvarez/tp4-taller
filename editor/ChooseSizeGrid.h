#ifndef TP4_TALLER_CHOOSESIZEGRID_H
#define TP4_TALLER_CHOOSESIZEGRID_H


#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include "Map.h"

class ChooseSizeGrid : public Gtk::Grid {
public:
    ChooseSizeGrid(BaseObjectType *obj,
                   Glib::RefPtr<Gtk::Builder> &builder,
                   Map &map);

private:
    void chooseSize();

    Map &map;
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::SpinButton *setWidth;
    Gtk::SpinButton *setHeight;
    Gtk::Button *okButton;
};


#endif //TP4_TALLER_CHOOSESIZEGRID_H
