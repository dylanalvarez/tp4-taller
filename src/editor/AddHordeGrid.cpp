#include <gtkmm/spinbutton.h>
#include "AddHordeGrid.h"

AddHordeGrid::AddHordeGrid(BaseObjectType *obj,
                           Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::Grid(obj),
        builder(builder),
        horde(DEFAULT_HORDE_TYPE,
              DEFAULT_HORDE_COUNT,
              DEFAULT_SECONDS_BEFORE_HORDE) {
    this->builder.get_widget("horde-quantity", hordeQuantityButton);
    hordeQuantityButton->signal_value_changed().connect(
            sigc::mem_fun(this, &AddHordeGrid::onChangeHordeQuantity));

    this->builder.get_widget("time-between-hordes", timeBeforeHordeButton);
    timeBeforeHordeButton->signal_value_changed().connect(
            sigc::mem_fun(this, &AddHordeGrid::onChangeTimeBefore));

    this->builder.get_widget("add-horde", addHordeButton);
    addHordeButton->signal_clicked().connect(
            sigc::mem_fun(this, &AddHordeGrid::onAddHorde));

    this->builder.get_widget("path-number", pathNumberSpinButton);
    this->builder.get_widget("horde-kind", hordeKindComboBox);
    hordeKindComboBox->append(Map::toString(Map::HordeType::greenDemon));
    hordeKindComboBox->append(Map::toString(Map::HordeType::goatMan));
    hordeKindComboBox->append(Map::toString(Map::HordeType::undead));
    hordeKindComboBox->append(Map::toString(Map::HordeType::spectre));
    hordeKindComboBox->append(Map::toString(Map::HordeType::bloodyHawk));
    hordeKindComboBox->append(Map::toString(Map::HordeType::abmonible));
    hordeKindComboBox->set_active(0);
    hordeKindComboBox->signal_changed().connect(
            sigc::mem_fun(this, &AddHordeGrid::onHordeKindChange));

    this->builder.get_widget("applied-hordes", hordeList);

    // set default value
    hordeQuantityButton->set_value(DEFAULT_HORDE_COUNT);
}

void AddHordeGrid::init(Map &map) { this->map = &map; }

void AddHordeGrid::onChangeHordeQuantity() {
    horde.quantity = hordeQuantityButton->get_value_as_int();
}

void AddHordeGrid::onChangeTimeBefore() {
    horde.secondsBeforeIt = timeBeforeHordeButton->get_value_as_int();
}

void AddHordeGrid::onAddHorde() {
    try {
        _addHordeToList(horde, map->addHorde(
                horde,
                pathNumberSpinButton->get_value_as_int()));
    } catch (std::exception& e) {}
}

void AddHordeGrid::_addHordeToList(Map::Horde horde,
                                   const std::string &pathName) {
    hordeList->set_text(hordeList->get_text()
                        + "\n" + horde.toString(pathName));
}

void AddHordeGrid::onHordeKindChange() {
    horde.type = Map::hordeTypeFromString(hordeKindComboBox->get_active_text());
}

void AddHordeGrid::setFromMap() {
    int pathNumber = 0;
    hordeList->set_text("");
    for (const Map::Path& path : map->getPaths()) {
        pathNumber++;
        for (const Map::Horde& horde: path.hordes) {
            _addHordeToList(horde, std::to_string(pathNumber));
        }
    }
}
