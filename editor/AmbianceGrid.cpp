#include <gtkmm/radiobutton.h>
#include "AmbianceGrid.h"

AmbianceGrid::AmbianceGrid(BaseObjectType *obj,
                           Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::Grid(obj),
        builder(builder),
        buttonIDs{{"desert",  Map::desert},
                  {"volcano", Map::volcano},
                  {"ice",     Map::ice},
                  {"meadow",  Map::meadow}} {

    for (auto pair : buttonIDs) {
        std::string id = pair.first;
        Gtk::RadioButton *button;
        this->builder.get_widget(id, button);
        button->signal_clicked().connect(
                sigc::bind<std::string>(
                        sigc::mem_fun(this, &AmbianceGrid::onChange), id));

    }

    // Group radio buttons together
    Gtk::RadioButton *desert;
    this->builder.get_widget("desert", desert);
    Gtk::RadioButton *volcano;
    this->builder.get_widget("volcano", volcano);
    volcano->join_group(*desert);
    Gtk::RadioButton *ice;
    this->builder.get_widget("ice", ice);
    ice->join_group(*desert);
    Gtk::RadioButton *meadow;
    this->builder.get_widget("meadow", meadow);
    meadow->join_group(*desert);

    // Set default value
    desert->set_active(true);
    if (map) { map->setSetting(DEFAULT_SETTING); }
}

void AmbianceGrid::onChange(std::string id) {
    if (map) { map->setSetting(buttonIDs[id]); }
}

void AmbianceGrid::init(Map &map) {
    this->map = &map;
}
