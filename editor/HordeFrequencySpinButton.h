#ifndef TP4_TALLER_HORDEFREQUENCYSPINBUTTON_H
#define TP4_TALLER_HORDEFREQUENCYSPINBUTTON_H


#include <gtkmm/spinbutton.h>
#include <gtkmm/builder.h>
#include "Map.h"

class HordeFrequencySpinButton : public Gtk::SpinButton {
public:
    HordeFrequencySpinButton(BaseObjectType *obj,
                             const Glib::RefPtr<Gtk::Builder> &builder);

    void init(Map &map);

private:
    void onChange();

    Map *map = nullptr;
};


#endif //TP4_TALLER_HORDEFREQUENCYSPINBUTTON_H
