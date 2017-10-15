#ifndef TP4_TALLER_SAVEBUTTON_H
#define TP4_TALLER_SAVEBUTTON_H


#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include "Map.h"

class SaveButton: public Gtk::Button {
public:
    SaveButton(BaseObjectType* obj,
               const Glib::RefPtr<Gtk::Builder>& builder,
               Map& map);

private:
    void onClick();

    Map& map;
};


#endif //TP4_TALLER_SAVEBUTTON_H
