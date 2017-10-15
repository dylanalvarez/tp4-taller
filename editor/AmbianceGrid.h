#ifndef TP4_TALLER_AMBIANCEGRID_H
#define TP4_TALLER_AMBIANCEGRID_H


#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include "Map.h"

class AmbianceGrid : public Gtk::Grid {
public:
    AmbianceGrid(BaseObjectType *obj,
                 Glib::RefPtr<Gtk::Builder> &builder,
                 Map &map);

private:
    void onChange(std::string id);

    Map &map;
    Glib::RefPtr<Gtk::Builder> builder;
    std::map<std::string, Map::Setting> buttonIDs;
};


#endif //TP4_TALLER_AMBIANCEGRID_H
