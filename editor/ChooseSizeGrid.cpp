#include <gtkmm/viewport.h>
#include "ChooseSizeGrid.h"
#include "MapGrid.h"

ChooseSizeGrid::ChooseSizeGrid(BaseObjectType *obj,
                               Glib::RefPtr<Gtk::Builder> &builder,
                               Map &map) : Gtk::Grid(obj),
                                           map(map),
                                           builder(builder) {
    builder->get_widget("set-y", setHeight);
    builder->get_widget("set-x", setWidth);
    builder->get_widget("choose-size", okButton);
    okButton->signal_clicked().connect(
            sigc::mem_fun(this, &ChooseSizeGrid::chooseSize));
}

void ChooseSizeGrid::chooseSize() {
    int width = setWidth->get_value_as_int();
    int height = setHeight->get_value_as_int();
    map.setSize(width, height);

    this->hide();
    Gtk::Grid* mainGrid;
    builder->get_widget("main-grid", mainGrid);
    mainGrid->show();

    Gtk::Viewport* mapViewport;
    builder->get_widget("map", mapViewport);

    auto mapGrid = Gtk::manage(new MapGrid(map, builder, width, height));
    mapViewport->add(*mapGrid);
    mapGrid->show();
}
