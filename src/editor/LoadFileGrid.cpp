#include <fstream>
#include <gtkmm/viewport.h>
#include <gtkmm/scrolledwindow.h>
#include "LoadFileGrid.h"
#include "MapGrid.h"
#include "NameEntry.h"

LoadFileGrid::LoadFileGrid(
        BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::Grid(obj), builder(builder) {
    this->builder.get_widget("file-name", fileNameEntry);
    this->builder.get_widget("load", loadButton);
    loadButton->signal_clicked().connect(
            sigc::mem_fun(this, &LoadFileGrid::loadFile));
}

void LoadFileGrid::init(Map &map, SaveButton *saveButton,
                        AmbianceGrid *ambianceGrid,
                        AddHordeGrid *addHordeGrid) {
    this->map = &map;
    this->saveButton = saveButton;
    this->ambianceGrid = ambianceGrid;
    this->addHordeGrid = addHordeGrid;
}

void LoadFileGrid::loadFile() {
    std::ifstream source(fileNameEntry->get_text() + ".yaml");
    if (!source.is_open()) { return; }
    map->loadFromFile(source);

    Gtk::Grid *initialGrid;
    builder.get_widget("initial-grid", initialGrid);
    initialGrid->hide();

    Gtk::Grid *mainGrid;
    builder.get_widget("main-grid", mainGrid);
    mainGrid->show();

    Gtk::ScrolledWindow *mapScrolledWindow;
    builder.get_widget("map", mapScrolledWindow);
    MapGrid *mapGrid = Gtk::manage(
            new MapGrid(*map, builder, map->getWidth(), map->getHeight(),
                        saveButton));
    mapScrolledWindow->add(*mapGrid);

    NameEntry *nameEntry;
    builder.get_widget_derived("name", nameEntry, *map, mapGrid);
    nameEntry->set_text(fileNameEntry->get_text());

    mapGrid->setFromMap();
    ambianceGrid->setFromMap();
    addHordeGrid->setFromMap();

    mapGrid->show();
}
