#ifndef TP4_TALLER_CONTROLLER_H
#define TP4_TALLER_CONTROLLER_H

#include <string>
#include <gtkmm/bin.h>
#include <gtkmm/builder.h>

class Controller {
public:
    virtual ~Controller() = default;

protected:
    Controller(Gtk::Bin *bin,
               std::string templateName,
               std::unique_ptr<Controller> &currentController);

    Gtk::Bin *parent;

    std::unique_ptr<Controller> &currentController;

    Glib::RefPtr<Gtk::Builder> builder;
};


#endif //TP4_TALLER_CONTROLLER_H
