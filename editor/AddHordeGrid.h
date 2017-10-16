#ifndef TP4_TALLER_ADDHORDEGRID_H
#define TP4_TALLER_ADDHORDEGRID_H


#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include "Map.h"

class AddHordeGrid : public Gtk::Grid {
public:
    AddHordeGrid(BaseObjectType *obj,
                 Glib::RefPtr<Gtk::Builder> &builder,
                 Map &map);

private:
    void onChangeHordeQuantity();

    void onAddHorde();

    void onClearHordes();

    void onHordeKindChange();

    Map &map;
    Glib::RefPtr<Gtk::Builder> builder;
    Map::Horde horde;
    Gtk::SpinButton *hordeQuantityButton;
    Gtk::Button *addHordeButton;
    Gtk::Label *hordeList;
    Gtk::Button *clearHordesButton;
    Gtk::ComboBoxText *hordeKindComboBox;
};


#endif //TP4_TALLER_ADDHORDEGRID_H
