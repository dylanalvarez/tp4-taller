#include "SaveButton.h"

SaveButton::SaveButton(BaseObjectType *obj,
                       const Glib::RefPtr<Gtk::Builder> &builder,
                       Map& map,
                       Glib::RefPtr<Gtk::Application>& app) :
        Gtk::Button(obj),
        map(map),
        app(app){
    this->signal_clicked().connect(sigc::mem_fun(this, &SaveButton::onClick));
}

void SaveButton::onClick() {
    map.exportToFile("output.yaml");
    app->quit();
}
