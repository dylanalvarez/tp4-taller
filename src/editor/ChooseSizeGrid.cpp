#include <gtkmm/viewport.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/messagedialog.h>
#include "ChooseSizeGrid.h"
#include "InvalidSizeException.h"

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
    try {
        map->resize(width, height);
    } catch (InvalidSizeException &e) {
        Gtk::MessageDialog dialog(e.what());
        dialog.set_transient_for(*(Gtk::Window *)
                this->get_parent()->get_parent()->get_parent());
        dialog.run();
        return;
    };
    Gtk::ScrolledWindow *mapScrolledWindow;
    builder.get_widget("map", mapScrolledWindow);
    delete mapScrolledWindow->get_child();
    MapGrid *mapGrid = Gtk::manage(
            new MapGrid(*map, builder, width, height, saveButton,
                        addHordeGrid));
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
    chooseSize();
}
