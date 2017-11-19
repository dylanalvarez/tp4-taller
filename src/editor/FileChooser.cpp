#include <fstream>
#include <gtkmm/scrolledwindow.h>
#include "FileChooser.h"

FileChooser::FileChooser(BaseObjectType *obj,
                         Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::FileChooserButton(obj), builder(builder) {}

void FileChooser::on_file_set() {
    std::ifstream source(this->get_filename());
    if (!source.is_open()) { return; }

    Gtk::ScrolledWindow *mapScrolledWindow;
    builder.get_widget("map", mapScrolledWindow);
    delete mapScrolledWindow->get_child();
    map->loadFromFile(source);
    MapGrid *mapGrid = Gtk::manage(
            new MapGrid(*map, builder, map->getWidth(), map->getHeight(),
                        saveButton));
    mapScrolledWindow->add(*mapGrid);
    nameEntry->addMapGridReference(mapGrid);
    nameEntry->setFromMap();
    mapGrid->setFromMap();
    ambianceGrid->setFromMap();
    addHordeGrid->setFromMap();

    mapGrid->show();
}

void
FileChooser::init(Map &map, SaveButton *saveButton, AmbianceGrid *ambianceGrid,
                  AddHordeGrid *addHordeGrid, NameEntry *nameEntry) {
    this->map = &map;
    this->saveButton = saveButton;
    this->ambianceGrid = ambianceGrid;
    this->addHordeGrid = addHordeGrid;
    this->nameEntry = nameEntry;

    Gtk::FileChooserDialog *dialog;
    builder.get_widget("filechooserdialog1", dialog);
    dialog->add_button("Cancelar", Gtk::RESPONSE_CANCEL);
    dialog->add_button("Abrir", Gtk::RESPONSE_OK);
}
