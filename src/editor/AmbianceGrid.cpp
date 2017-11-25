#include "AmbianceGrid.h"

AmbianceGrid::AmbianceGrid(BaseObjectType *obj,
                           Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::Grid(obj),
        builder(builder),
        buttonIDs{{"desert",  Map::Setting::desert},
                  {"volcano", Map::Setting::volcano},
                  {"ice",     Map::Setting::ice},
                  {"meadow",  Map::Setting::meadow}} {

    for (auto pair : buttonIDs) {
        const auto &id = pair.first;
        Gtk::RadioButton *button;
        this->builder.get_widget(id, button);
        button->signal_clicked().connect(
                sigc::bind<const std::string&>(
                        sigc::mem_fun(this, &AmbianceGrid::onChange), id));

    }

    // Group radio buttons together
    this->builder.get_widget("desert", desert);
    this->builder.get_widget("volcano", volcano);
    volcano->join_group(*desert);
    this->builder.get_widget("ice", ice);
    ice->join_group(*desert);
    this->builder.get_widget("meadow", meadow);
    meadow->join_group(*desert);

    // Set default value
    desert->set_active(true);
    if (map) { map->setSetting(DEFAULT_SETTING); }
}

void AmbianceGrid::onChange(const std::string &id) {
    if (map) { map->setSetting(buttonIDs[id]); }
}

void AmbianceGrid::init(Map &map) {
    this->map = &map;
}

void AmbianceGrid::setFromMap() {
    switch (map->getSetting()) {
        case Map::Setting::desert:
            desert->set_active(true);
            break;
        case Map::Setting::volcano:
            volcano->set_active(true);
            break;
        case Map::Setting::ice:
            ice->set_active(true);
            break;
        case Map::Setting::meadow:
            meadow->set_active(true);
            break;
    }
}
