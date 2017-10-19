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

private:
    void setSquareType(MapGrid::SquareType squareType);

    bool isValidStartPosition(int x, int y) const;

    std::vector<std::vector<Gtk::Button*>> grid;
    Builder& builder;
    SquareType squareType;
    int width, height;
};


#endif //TP4_TALLER_MAPGRID_H
