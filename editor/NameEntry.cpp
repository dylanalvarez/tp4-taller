#include "NameEntry.h"

NameEntry::NameEntry(BaseObjectType *obj,
                     const Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::Entry(obj) {
    this->signal_key_release_event().connect(
            sigc::mem_fun(this, &NameEntry::onKeyRelease));
}

void NameEntry::init(Map &map, MapGrid *mapGrid) {
    this->map = &map;
    this->mapGrid = mapGrid;
}

bool NameEntry::onKeyRelease(GdkEventKey *event) {
    bool stopPropagation = true;
    map->setName(this->get_text());
    mapGrid->updateDisabledButtons();
    return stopPropagation;
}
