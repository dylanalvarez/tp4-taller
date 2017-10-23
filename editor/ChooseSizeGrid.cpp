#include <gtkmm/viewport.h>
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
    map->setSize(width, height);

    Gtk::Grid *initialGrid;
    builder.get_widget("initial-grid", initialGrid);
    initialGrid->hide();

    Gtk::Grid *mainGrid;
    builder.get_widget("main-grid", mainGrid);
    mainGrid->show();

    Gtk::Viewport *mapViewport;
    builder.get_widget("map", mapViewport);

    MapGrid *mapGrid = Gtk::manage(
            new MapGrid(*map, builder, width, height, saveButton));
    mapViewport->add(*mapGrid);

    NameEntry *nameEntry;
    builder.get_widget_derived("name", nameEntry, *map, mapGrid);

    mapGrid->show();
}

void ChooseSizeGrid::init(Map &map, SaveButton *saveButton) {
    this->map = &map;
    this->saveButton = saveButton;
}
