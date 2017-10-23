#include "MapButton.h"

MapButton::MapButton(
        const Glib::ustring &label,
        int x, int y, MapGrid &parent, Map &map) :
        Gtk::Button(label), x(x), y(y), map(map) {
    this->signal_clicked().connect(
            sigc::bind<MapGrid &>(
                    sigc::mem_fun(this, &MapButton::setSquareType),
                    parent));
}

void MapButton::setSquareType(MapGrid &parent) {
    MapGrid::SquareType squareType = parent.getSquareType();
    switch (squareType) {
        case MapGrid::start:
            set_label(ENTRY_DOOR_STR);
            map.addEntryDoor(x, y);
            break;
        case MapGrid::end:
            set_label(EXIT_DOOR_STR);
            map.addExitDoor(x, y);
            break;
        case MapGrid::firmGround:
            set_label(FIRM_GROUND_STR);
            map.addFirmGround(x, y);
            break;
        case MapGrid::path:
            break;
    }
    parent.notifyGridClicked(x, y, squareType);
}
