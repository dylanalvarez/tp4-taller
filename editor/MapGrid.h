#ifndef TP4_TALLER_MAPGRID_H
#define TP4_TALLER_MAPGRID_H


#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include "Map.h"
#include "Builder.h"

class MapGrid : public Gtk::Grid {
public:
    MapGrid(Map &map,
            Builder &builder,
            int width,
            int height);

    enum SquareType {
        start, end, firmGround, path
    };

    MapGrid::SquareType getSquareType() const;

    void updateDisabledButtons() const;

    void notifyClicked(int x, int y, SquareType squareType);

private:
    void setSquareType(MapGrid::SquareType squareType);

    std::vector<std::vector<Gtk::Button *>> grid;
    Builder &builder;
    SquareType squareType;
    int width;
    int height;
    int lastX;
    int lastY;
};


#endif //TP4_TALLER_MAPGRID_H
