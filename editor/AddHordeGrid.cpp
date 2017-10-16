#include <gtkmm/spinbutton.h>
#include "AddHordeGrid.h"

AddHordeGrid::AddHordeGrid(BaseObjectType *obj,
                           Glib::RefPtr<Gtk::Builder> &builder, Map &map) :
        Gtk::Grid(obj),
        map(map),
        builder(builder),
        horde(DEFAULT_HORDE_TYPE, DEFAULT_HORDE_COUNT) {
    builder->get_widget("horde-quantity", hordeQuantityButton);
    hordeQuantityButton->signal_value_changed().connect(
            sigc::mem_fun(this, &AddHordeGrid::onChangeHordeQuantity));

    builder->get_widget("add-horde", addHordeButton);
    addHordeButton->signal_clicked().connect(
            sigc::mem_fun(this, &AddHordeGrid::onAddHorde));

    builder->get_widget("clear-hordes", clearHordesButton);
    clearHordesButton->signal_clicked().connect(
            sigc::mem_fun(this, &AddHordeGrid::onClearHordes));

    builder->get_widget("clear-hordes", clearHordesButton);
    clearHordesButton->signal_clicked().connect(
            sigc::mem_fun(this, &AddHordeGrid::onClearHordes));

    builder->get_widget("horde-kind", hordeKindComboBox);
    hordeKindComboBox->append(Map::toString(Map::greenDemon));
    hordeKindComboBox->append(Map::toString(Map::goatMan));
    hordeKindComboBox->append(Map::toString(Map::undead));
    hordeKindComboBox->append(Map::toString(Map::spectre));
    hordeKindComboBox->append(Map::toString(Map::bloodyHawk));
    hordeKindComboBox->append(Map::toString(Map::abmonible));
    hordeKindComboBox->set_active(0);
    hordeKindComboBox->signal_changed().connect(sigc::mem_fun(this, &AddHordeGrid::onHordeKindChange));

    builder->get_widget("applied-hordes", hordeList);

    // set default value
    hordeQuantityButton->set_value(DEFAULT_HORDE_COUNT);
}

void AddHordeGrid::onChangeHordeQuantity() {
    horde.quantity = hordeQuantityButton->get_value_as_int();
}

void AddHordeGrid::onAddHorde() {
    map.addHorde(horde);
    hordeList->set_text(hordeList->get_text() + "\n" + horde.toString());
}

void AddHordeGrid::onClearHordes() {
    map.clearHordes();
    hordeList->set_text("");
}

void AddHordeGrid::onHordeKindChange() {
    horde.type = Map::fromString(hordeKindComboBox->get_active_text());
}
