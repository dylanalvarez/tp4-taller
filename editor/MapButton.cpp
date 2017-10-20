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
            set_label("E");
            map.addEntryDoor(x, y);
            break;
        case MapGrid::end:
            set_label("S");
            map.addExitDoor(x, y);
            break;
        case MapGrid::firmGround:
            set_label("T");
            map.addFirmGround(x, y);
            break;
        case MapGrid::path:
            set_label("C");
            map.addPathStep(x, y);
            break;
    }
    parent.notifyClicked(x, y, squareType);
}
