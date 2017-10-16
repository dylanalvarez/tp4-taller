#include <gtkmm/radiobutton.h>
#include "AmbianceGrid.h"

AmbianceGrid::AmbianceGrid(BaseObjectType *obj,
                           Glib::RefPtr<Gtk::Builder> &builder,
                           Map &map) :
        Gtk::Grid(obj),
        map(map),
        builder(builder),
        buttonIDs{{"desert",  Map::desert},
                  {"volcano", Map::volcano},
                  {"ice",     Map::ice},
                  {"meadow",  Map::meadow}} {

    for (auto pair : buttonIDs) {
        std::string id = pair.first;
        Gtk::RadioButton *button;
        builder->get_widget(id, button);
        button->signal_clicked().connect(
                sigc::bind<std::string>(
                        sigc::mem_fun(this, &AmbianceGrid::onChange), id));

    }

    // Group radio buttons together
    Gtk::RadioButton *desert;
    builder->get_widget("desert", desert);
    Gtk::RadioButton *volcano;
    builder->get_widget("volcano", volcano);
    volcano->join_group(*desert);
    Gtk::RadioButton *ice;
    builder->get_widget("ice", ice);
    ice->join_group(*desert);
    Gtk::RadioButton *meadow;
    builder->get_widget("meadow", meadow);
    meadow->join_group(*desert);

    // Set default value
    desert->set_active(true);
    map.setSetting(DEFAULT_SETTING);
}

void AmbianceGrid::onChange(std::string id) {
    map.setSetting(buttonIDs[id]);
}
