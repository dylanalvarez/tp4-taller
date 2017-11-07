#ifndef TP4_TALLER_ADDHORDEGRID_H
#define TP4_TALLER_ADDHORDEGRID_H


#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/spinbutton.h>
#include "Map.h"
#include "Builder.h"

class AddHordeGrid : public Gtk::Grid {
public:
    AddHordeGrid(BaseObjectType *obj,
                 Glib::RefPtr<Gtk::Builder> &builder);

    void init(Map &map);

    void setFromMap();

private:
    void onChangeHordeQuantity();

    void onChangeTimeBefore();

    void onAddHorde();

    void onHordeKindChange();

    void _addHordeToList(Map::Horde horde, const std::string &pathName);

    Map *map = nullptr;
    Builder builder;
    Map::Horde horde;
    Gtk::SpinButton *hordeQuantityButton;
    Gtk::SpinButton *timeBeforeHordeButton;
    Gtk::Button *addHordeButton;
    Gtk::Label *hordeList;
    Gtk::ComboBoxText *hordeKindComboBox;
    Gtk::SpinButton *pathNumberSpinButton;
};


#endif //TP4_TALLER_ADDHORDEGRID_H
