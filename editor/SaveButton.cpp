#include "SaveButton.h"

SaveButton::SaveButton(BaseObjectType *obj,
                       const Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::Button(obj) {
    this->signal_clicked().connect(sigc::mem_fun(this, &SaveButton::onClick));
}

void SaveButton::init(Map &map, Glib::RefPtr<Gtk::Application> &app) {
    this->map = &map;
    this->app = &app;
}

void SaveButton::onClick() {
    map->exportToFile("output.yaml");
    (*app)->quit();
}
