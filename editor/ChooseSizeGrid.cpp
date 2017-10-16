#include "ChooseSizeGrid.h"

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
    map.setSize(setWidth->get_value_as_int(), setHeight->get_value_as_int());
    this->hide();
    Gtk::Grid* mainGrid;
    builder->get_widget("main-grid", mainGrid);
    mainGrid->show();
}
