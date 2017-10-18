#ifndef TP4_TALLER_MAPGRID_H
#define TP4_TALLER_MAPGRID_H


#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
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

private:
    void setSquareType(MapGrid::SquareType squareType);

    Builder& builder;
    SquareType squareType;
};


#endif //TP4_TALLER_MAPGRID_H
