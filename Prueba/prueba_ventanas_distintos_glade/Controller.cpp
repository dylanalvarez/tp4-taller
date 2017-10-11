#include <gtkmm/builder.h>
#include <string>
#include <iostream>
#include "Controller.h"

Controller::Controller(Gtk::Bin *bin,
                       std::string templateName,
                       std::unique_ptr<Controller> &currentController) :
        parent(bin),
        currentController(currentController),
        builder(Gtk::Builder::create_from_file(
                "assets/glade/" + templateName + ".glade")) {
    // hide existing children
    parent->remove();
    // make myself parent's children
    Gtk::Container *container = nullptr;
    builder->get_widget("container", container);
    parent->add(*container);
}
