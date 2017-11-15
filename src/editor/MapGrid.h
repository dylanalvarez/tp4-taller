#ifndef TP4_TALLER_MAPGRID_H
#define TP4_TALLER_MAPGRID_H


#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include "Map.h"
#include "Builder.h"
#include "SaveButton.h"

class MapGrid : public Gtk::Grid {
public:
    MapGrid(Map &map,
            Builder &builder,
            int width,
            int height,
            SaveButton *saveButton);

    enum SquareType {
        start, end, firmGround, path
    };

    MapGrid::SquareType getSquareType() const;

    void updateDisabledButtons() const;

    void notifyGridClicked(int x, int y, SquareType squareType);

    void setFromMap();

private:
    void setSquareType(MapGrid::SquareType squareType);

    void updateDisabledButton(int x, int y) const;

    bool shouldBeDisabled(int x, int y) const;

    bool isNeighbourOfStart(int x, int y) const;

    bool isOnStraightLineFromLastOne(int x, int y) const;

    bool isOnTheWayOfAPath(int x, int y) const;

    std::vector<std::vector<Gtk::Button *>> grid;
    Builder &builder;
    SquareType squareType;
    int width;
    int height;
    int lastPathX;
    int lastPathY;
    int startX;
    int startY;
    bool unfinishedPath;
    bool justStartedPath;
    Map &map;
    Gtk::RadioButton *startButton;
    Gtk::RadioButton *endButton;
    Gtk::RadioButton *firmGroundButton;
    Gtk::RadioButton *pathButton;
    SaveButton *saveButton;
};


#endif //TP4_TALLER_MAPGRID_H
