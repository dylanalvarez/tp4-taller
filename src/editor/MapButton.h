#ifndef TP4_TALLER_MAPBUTTON_H
#define TP4_TALLER_MAPBUTTON_H

#define FIRM_GROUND_STR std::string("T")
#define ENTRY_DOOR_STR std::string("E")
#define EXIT_DOOR_STR std::string("S")

#include <gtkmm/button.h>
#include "Map.h"

class MapGrid;

class MapButton : public Gtk::Button {
public:
    MapButton(const Glib::ustring &label,
              int x, int y, MapGrid &parent, Map &map);

    void setColor(const Gdk::RGBA &color);

private:
    void setSquareType(MapGrid &parent);

    int x, y;
    Map &map;
};


#endif //TP4_TALLER_MAPBUTTON_H
