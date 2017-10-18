#ifndef TP4_TALLER_AMBIANCEGRID_H
#define TP4_TALLER_AMBIANCEGRID_H


#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include "Map.h"
#include "Builder.h"

class AmbianceGrid : public Gtk::Grid {
public:
    AmbianceGrid(BaseObjectType *obj,
                 Glib::RefPtr<Gtk::Builder> &builder);

    void init(Map& map);

private:
    void onChange(std::string id);

    Map *map = nullptr;
    Builder builder;
    std::map<std::string, Map::Setting> buttonIDs;
};


#endif //TP4_TALLER_AMBIANCEGRID_H
