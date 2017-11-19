#include <gtkmm/viewport.h>
#include <gtkmm/scrolledwindow.h>
#include "ChooseSizeGrid.h"
#include "MapGrid.h"
#include "NameEntry.h"

ChooseSizeGrid::ChooseSizeGrid(BaseObjectType *obj,
                               Glib::RefPtr<Gtk::Builder> &builder) :
        Gtk::Grid(obj),
        builder(builder) {
    this->builder.get_widget("set-y", setHeight);
    this->builder.get_widget("set-x", setWidth);
    this->builder.get_widget("choose-size", okButton);
    okButton->signal_clicked().connect(
            sigc::mem_fun(this, &ChooseSizeGrid::chooseSize));
}

void ChooseSizeGrid::chooseSize() {
    int width = setWidth->get_value_as_int();
    int height = setHeight->get_value_as_int();

    Gtk::ScrolledWindow *mapScrolledWindow;
    builder.get_widget("map", mapScrolledWindow);
    delete mapScrolledWindow->get_child();
    map->reset(width, height);

    MapGrid *mapGrid = Gtk::manage(
            new MapGrid(*map, builder, width, height, saveButton));
    mapScrolledWindow->add(*mapGrid);
    nameEntry->addMapGridReference(mapGrid);

    mapGrid->setFromMap();
    ambianceGrid->setFromMap();
    addHordeGrid->setFromMap();

    mapGrid->show();
}

void ChooseSizeGrid::init(Map &map, SaveButton *saveButton,
                          AmbianceGrid *ambianceGrid,
                          AddHordeGrid *addHordeGrid, NameEntry *nameEntry) {
    this->map = &map;
    this->saveButton = saveButton;
    this->ambianceGrid = ambianceGrid;
    this->addHordeGrid = addHordeGrid;
    this->nameEntry = nameEntry;
}
