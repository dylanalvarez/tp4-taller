#include "SaveButton.h"

SaveButton::SaveButton(BaseObjectType *obj,
                       const Glib::RefPtr<Gtk::Builder> &builder,
                       Map& map) : Gtk::Button(obj), map(map) {
    this->signal_clicked().connect(sigc::mem_fun(this, &SaveButton::onClick));
}

void SaveButton::onClick() {
    map.exportToFile("output.yaml");
}
