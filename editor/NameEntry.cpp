#include "NameEntry.h"

NameEntry::NameEntry(BaseObjectType *obj,
                     const Glib::RefPtr<Gtk::Builder> &builder,
                     Map &map) : Gtk::Entry(obj), map(map) {
    this->signal_key_release_event().connect(
            sigc::mem_fun(this, &NameEntry::onKeyRelease));
}

bool NameEntry::onKeyRelease(GdkEventKey *event) {
    bool stopPropagation = true;
    map.setName(this->get_text());
    return stopPropagation;
}
