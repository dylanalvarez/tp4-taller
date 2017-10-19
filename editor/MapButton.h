#ifndef TP4_TALLER_MAPBUTTON_H
#define TP4_TALLER_MAPBUTTON_H


#include <gtkmm/button.h>
#include "Map.h"
#include "MapGrid.h"

class MapButton : public Gtk::Button {
public:
    MapButton(const Glib::ustring &label,
              int x, int y, const MapGrid &parent, Map &map);

private:
    void setSquareType(const MapGrid &parent);

    int x, y;
    Map &map;
};


#endif //TP4_TALLER_MAPBUTTON_H
