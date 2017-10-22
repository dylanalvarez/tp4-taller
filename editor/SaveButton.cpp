#include "SaveButton.h"

SaveButton::SaveButton(BaseObjectType *obj,
                       const Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::Button(obj) {
    this->signal_clicked().connect(sigc::mem_fun(this, &SaveButton::onClick));
    this->set_sensitive(false);
}

void SaveButton::init(Map &map) { this->map = &map; }

void SaveButton::onClick() {
    map->exportToFile(map->getName() + ".yaml");
}
