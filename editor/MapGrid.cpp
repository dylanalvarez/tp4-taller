#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include "MapGrid.h"
#include "MapButton.h"

MapGrid::MapGrid(Map &map,
                 Builder &builder,
                 int width,
                 int height) : builder(builder), squareType(start) {
    for (int x = 0; x <= width + 1; x++) {
        for (int y = 0; y <= height + 1; y++) {
            auto square = Gtk::manage(new MapButton("", x, y, *this, map));
            attach(*square, x, y, 1, 1);
            square->show();
        }
    }

    // Group radio buttons together
    Gtk::RadioButton *start;
    this->builder.get_widget("start", start);
    Gtk::RadioButton *end;
    this->builder.get_widget("end", end);
    end->join_group(*start);
    Gtk::RadioButton *firmGround;
    this->builder.get_widget("firm-ground", firmGround);
    firmGround->join_group(*start);
    Gtk::RadioButton *path;
    this->builder.get_widget("path", path);
    path->join_group(*start);

    start->signal_clicked().connect(
            sigc::bind<MapGrid::SquareType>(
                    sigc::mem_fun(this, &MapGrid::setSquareType),
                    MapGrid::start));
    end->signal_clicked().connect(
            sigc::bind<MapGrid::SquareType>(
                    sigc::mem_fun(this, &MapGrid::setSquareType),
                    MapGrid::end));
    firmGround->signal_clicked().connect(
            sigc::bind<MapGrid::SquareType>(
                    sigc::mem_fun(this, &MapGrid::setSquareType),
                    MapGrid::firmGround));
    path->signal_clicked().connect(
            sigc::bind<MapGrid::SquareType>(
                    sigc::mem_fun(this, &MapGrid::setSquareType),
                    MapGrid::path));

    // Set default value
    start->set_active(true);
}

void MapGrid::setSquareType(MapGrid::SquareType squareType) {
    this->squareType = squareType;
}

MapGrid::SquareType MapGrid::getSquareType() const {
    return squareType;
}
