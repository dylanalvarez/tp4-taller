#ifndef TP4_TALLER_SAVEBUTTON_H
#define TP4_TALLER_SAVEBUTTON_H


#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/application.h>
#include "Map.h"

class SaveButton : public Gtk::Button {
public:
    SaveButton(BaseObjectType *obj,
               const Glib::RefPtr<Gtk::Builder> &builder);

    void init(Map &map, Gtk::Window *mainWindow);

private:
    void onClick();

    Map *map = nullptr;
    Gtk::Window *mainWindow;
};


#endif //TP4_TALLER_SAVEBUTTON_H
