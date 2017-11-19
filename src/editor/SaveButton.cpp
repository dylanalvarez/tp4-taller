#include <gtkmm/filechooserdialog.h>
#include "SaveButton.h"

SaveButton::SaveButton(BaseObjectType *obj,
                       const Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::Button(obj) {
    this->signal_clicked().connect(sigc::mem_fun(this, &SaveButton::onClick));
    this->set_sensitive(false);
}

void SaveButton::init(Map &map, Gtk::Window *mainWindow) {
    this->map = &map;
    this->mainWindow = mainWindow;
}

void SaveButton::onClick() {
    Gtk::FileChooserDialog dialog("", Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*mainWindow);
    dialog.add_button("Cancelar", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Guardar", Gtk::RESPONSE_OK);
    if (dialog.run() == Gtk::RESPONSE_OK) {
        map->exportToFile(dialog.get_filename());
    }
}
