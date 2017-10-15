#ifndef TP4_TALLER_NAMEENTRY_H
#define TP4_TALLER_NAMEENTRY_H


#include <gtkmm/entry.h>
#include <gtkmm/builder.h>
#include "Map.h"

class NameEntry : public Gtk::Entry {
public:
    NameEntry(BaseObjectType *obj,
              const Glib::RefPtr<Gtk::Builder> &builder,
              Map &map);

private:
    bool onKeyRelease(GdkEventKey *event);

    Map& map;
};


#endif //TP4_TALLER_NAMEENTRY_H
