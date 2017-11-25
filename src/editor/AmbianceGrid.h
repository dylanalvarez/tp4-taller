#ifndef TP4_TALLER_AMBIANCEGRID_H
#define TP4_TALLER_AMBIANCEGRID_H


#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include <gtkmm/radiobutton.h>
#include "Map.h"
#include "Builder.h"

class AmbianceGrid : public Gtk::Grid {
public:
    AmbianceGrid(BaseObjectType *obj,
                 Glib::RefPtr<Gtk::Builder> &builder);

    void init(Map &map);

    void setFromMap();

private:
    void onChange(const std::string &id);

    Map *map = nullptr;
    Builder builder;
    std::map<std::string, Map::Setting> buttonIDs;
    Gtk::RadioButton *desert;
    Gtk::RadioButton *volcano;
    Gtk::RadioButton *ice;
    Gtk::RadioButton *meadow;
};


#endif //TP4_TALLER_AMBIANCEGRID_H
