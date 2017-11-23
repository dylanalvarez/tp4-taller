#include <gtkmm/cssprovider.h>
#include "MapButton.h"
#include "MapGrid.h"
#define PRIORITY 10

MapButton::MapButton(
        const Glib::ustring &label,
        int x, int y, MapGrid &parent, Map &map) :
        Gtk::Button(label), x(x), y(y), map(map) {
    this->signal_clicked().connect(
            sigc::bind<MapGrid &>(
                    sigc::mem_fun(this, &MapButton::setSquareType),
                    parent));
    this->set_size_request(60, 60);
}

void MapButton::setSquareType(MapGrid &parent) {
    MapGrid::SquareType squareType = parent.getSquareType();
    switch (squareType) {
        case MapGrid::start:
            set_label(ENTRY_DOOR_STR + map.addEntryDoor(x, y));
            break;
        case MapGrid::end:
            set_label(EXIT_DOOR_STR + map.addExitDoor(x, y));
            break;
        case MapGrid::firmGround:
            set_label(FIRM_GROUND_STR);
            map.addFirmGround(x, y);
            break;
        case MapGrid::path:
            break;
        case MapGrid::deletePath:
            map.deletePathWithEntryIn(x, y);
    }
    parent.notifyGridClicked(x, y, squareType);
}

void MapButton::setColor(const Gdk::RGBA &color) {
    auto *label = dynamic_cast<Gtk::Label *>(this->get_child());
    Glib::RefPtr<Gtk::CssProvider> css = Gtk::CssProvider::create();
    css->load_from_data(
            "* {"
                    "border-radius: 50%;"
#ifdef __APPLE__
                    "min-width: 20px;"
                    "min-height: 20px;"
#endif
                    "margin: 12px 0;"
                    "color: white;"
                    "font-weight: bold;"
            "  }");
    label->get_style_context()->add_provider(css, PRIORITY);
    label->override_background_color(color);
    label->override_color(Gdk::RGBA("white"));
}
