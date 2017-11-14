#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include "MapGrid.h"
#include "MapButton.h"

MapGrid::MapGrid(Map &map,
                 Builder &builder,
                 int width,
                 int height,
                 SaveButton *saveButton) :
        builder(builder), squareType(start), width(width), height(height),
        lastPathX(-1), lastPathY(-1), startX(-1), startY(-1),
        unfinishedPath(false), justStartedPath(false), map(map),
        saveButton(saveButton) {
    for (int x = 0; x <= width + 1; x++) {
        grid.emplace_back();
        for (int y = 0; y <= height + 1; y++) {
            auto square = Gtk::manage(new MapButton("", x, y, *this, map));
            attach(*square, x, y, 1, 1);
            square->set_size_request(30, 30);
            square->show();
            grid[x].push_back((Gtk::Button *) square);
        }
    }

    // Group radio buttons together
    this->builder.get_widget("start", startButton);
    this->builder.get_widget("end", endButton);
    endButton->join_group(*startButton);
    this->builder.get_widget("firm-ground", firmGroundButton);
    firmGroundButton->join_group(*startButton);
    this->builder.get_widget("path", pathButton);
    pathButton->join_group(*startButton);

    startButton->signal_clicked().connect(
            sigc::bind<MapGrid::SquareType>(
                    sigc::mem_fun(this, &MapGrid::setSquareType),
                    MapGrid::start));
    endButton->signal_clicked().connect(
            sigc::bind<MapGrid::SquareType>(
                    sigc::mem_fun(this, &MapGrid::setSquareType),
                    MapGrid::end));
    firmGroundButton->signal_clicked().connect(
            sigc::bind<MapGrid::SquareType>(
                    sigc::mem_fun(this, &MapGrid::setSquareType),
                    MapGrid::firmGround));
    pathButton->signal_clicked().connect(
            sigc::bind<MapGrid::SquareType>(
                    sigc::mem_fun(this, &MapGrid::setSquareType),
                    MapGrid::path));

    // Set default value
    startButton->set_active(true);
    this->updateDisabledButtons();
}

void MapGrid::setFromMap() {
    for (const Map::Coordinate& firmGround : map.getFirmGround()){
        grid[firmGround.x][firmGround.y]->set_label(FIRM_GROUND_STR);
    }
    int pathNumber = 1;
    for (const Map::Path& path : map.getPaths()){
        std::string pathLabel = std::to_string(pathNumber);
        grid[path.entry.x][path.entry.y]->set_label(ENTRY_DOOR_STR + pathLabel);
        grid[path.exit.x][path.exit.y]->set_label(EXIT_DOOR_STR + pathLabel);
        int stepNumber = 1;
        for (const Map::Coordinate& pathStep : path.pathSequence) {
            grid[pathStep.x][pathStep.y]->set_label(PATH_STR
                                                    + pathLabel
                                                    + ", "
                                                    + std::to_string(
                    stepNumber));
            stepNumber++;
        }
        pathNumber++;
    }
    updateDisabledButtons();
}

void MapGrid::setSquareType(MapGrid::SquareType squareType) {
    this->squareType = squareType;
    this->updateDisabledButtons();
}

MapGrid::SquareType MapGrid::getSquareType() const {
    return squareType;
}

void MapGrid::updateDisabledButtons() const {
    saveButton->set_sensitive(!unfinishedPath &&
                              !map.getName().empty());
    for (int x = 0; x <= width + 1; x++) {
        for (int y = 0; y <= height + 1; y++) {
            updateDisabledButton(x, y);
        }
    }
}

void MapGrid::updateDisabledButton(int x, int y) const {
    Gtk::Button *button = grid[x][y];
    bool isMarked = !button->get_label().empty();
    button->set_sensitive(!(isMarked || shouldBeDisabled(x, y)));
}

bool MapGrid::shouldBeDisabled(int x, int y) const {
    bool isCorner = (x == 0 && y == 0) ||
                    (x == 0 && y == height + 1) ||
                    (x == width + 1 && y == 0) ||
                    (x == width + 1 && y == height + 1);

    bool isOnTheEdge = x == 0 || x == width + 1 || y == 0 || y == height + 1;
    bool lastPathStepWasOnItsSide =
            (std::abs(x - lastPathX) == 1 && std::abs(y - lastPathY) == 0) ||
            (std::abs(x - lastPathX) == 0 && std::abs(y - lastPathY) == 1);
    bool makesSenseForCurrentSquareType =
            (squareType == start &&
             isOnTheEdge &&
             !unfinishedPath) ||
            (squareType == end &&
             isOnTheEdge &&
             unfinishedPath &&
             lastPathStepWasOnItsSide) ||
            (squareType == path &&
             !isOnTheEdge &&
             (isNeighbourOfStart(x, y) || !justStartedPath) &&
             isOnStraightLineFromLastOne(x, y)) ||
            (squareType == firmGround &&
             !isOnTheEdge &&
             !isNeighbourOfStart(x, y));

    return isCorner || !makesSenseForCurrentSquareType;
}

void MapGrid::notifyGridClicked(int x, int y, SquareType squareType) {
    if (squareType == end) {
        unfinishedPath = false;
        lastPathX = -1;
        lastPathY = -1;
    }
    if (squareType == start) {
        startX = x;
        startY = y;
        pathButton->clicked();
        unfinishedPath = true;
        justStartedPath = true;
    }
    if (squareType == path) {
        grid[x][y]->set_label(PATH_STR
                              + map.addPathStep(x, y)
                              + ", "
                              + std::to_string(
                map.getPaths().back().pathSequence.size()));

        this->lastPathX = x;
        this->lastPathY = y;
        justStartedPath = false;
    }
    this->updateDisabledButtons();
}

bool MapGrid::isNeighbourOfStart(int x, int y) const {
    return grid[x - 1][y]->get_label().substr(0, 1) == ENTRY_DOOR_STR ||
           grid[x][y - 1]->get_label().substr(0, 1) == ENTRY_DOOR_STR ||
           grid[x + 1][y]->get_label().substr(0, 1) == ENTRY_DOOR_STR ||
           grid[x][y + 1]->get_label().substr(0, 1) == ENTRY_DOOR_STR;
}

bool MapGrid::isOnStraightLineFromLastOne(int x, int y) const {
    int lastX = lastPathX == -1 ? startX : lastPathX;
    int lastY = lastPathY == -1 ? startY : lastPathY;
    return x == lastX || y == lastY;
}
