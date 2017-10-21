#ifndef TP4_TALLER_CHOOSESIZEGRID_H
#define TP4_TALLER_CHOOSESIZEGRID_H


#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include "Map.h"
#include "Builder.h"
#include "SaveButton.h"

class ChooseSizeGrid : public Gtk::Grid {
public:
    ChooseSizeGrid(BaseObjectType *obj,
                   Glib::RefPtr<Gtk::Builder> &builder);

    void init(Map &map, SaveButton *saveButton);

private:
    void chooseSize();

    Map *map = nullptr;
    Builder builder;
    Gtk::SpinButton *setWidth;
    Gtk::SpinButton *setHeight;
    Gtk::Button *okButton;
    SaveButton *saveButton;
};


#endif //TP4_TALLER_CHOOSESIZEGRID_H
