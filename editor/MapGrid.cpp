#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include <cmath>
#include "MapGrid.h"
#include "MapButton.h"

MapGrid::MapGrid(Map &map,
                 Builder &builder,
                 int width,
                 int height,
                 SaveButton *saveButton) :
        builder(builder), squareType(start), width(width), height(height),
        lastPathX(-1), lastPathY(-1), startX(-1), startY(-1),
        unfinishedPath(false), map(map), saveButton(saveButton) {
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

void MapGrid::setSquareType(MapGrid::SquareType squareType) {
    this->squareType = squareType;
    this->updateDisabledButtons();
}

MapGrid::SquareType MapGrid::getSquareType() const {
    return squareType;
}

void MapGrid::updateDisabledButtons() const {
    saveButton->set_sensitive(startX != -1 &&
                              !unfinishedPath &&
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
    }
    if (squareType == path) {
        int lastX = lastPathX == -1 ? startX : lastPathX;
        int lastY = lastPathY == -1 ? startY : lastPathY;
        bool sharesPathOnX = x == lastX;
        bool sharesPathOnY = y == lastY;
        if (sharesPathOnX) {
            bool yIsGreater = y > lastY;
            int start = yIsGreater ? lastY + 1 : y;
            int end = yIsGreater ? y : lastY - 1;
            for (int currentY = start; currentY <= end; ++currentY) {
                grid[x][currentY]->set_label("C");
                map.addPathStep(x, currentY);
            }
        } else if (sharesPathOnY) {
            bool xIsGreater = x > lastX;
            int start = xIsGreater ? lastX + 1 : x;
            int end = xIsGreater ? x : lastX - 1;
            for (int currentX = start; currentX <= end; ++currentX) {
                grid[currentX][y]->set_label("C");
                map.addPathStep(currentX, y);
            }
        }
        this->lastPathX = x;
        this->lastPathY = y;
    }
    this->updateDisabledButtons();
}

bool MapGrid::isNeighbourOfStart(int x, int y) const {
    return grid[x - 1][y]->get_label() == "E" ||
           grid[x][y - 1]->get_label() == "E" ||
           grid[x + 1][y]->get_label() == "E" ||
           grid[x][y + 1]->get_label() == "E";
}

bool MapGrid::isOnStraightLineFromLastOne(int x, int y) const {
    int lastX = lastPathX == -1 ? startX : lastPathX;
    int lastY = lastPathY == -1 ? startY : lastPathY;
    bool sharesPathOnX = x == lastX;
    bool sharesPathOnY = y == lastY;
    if (sharesPathOnX) {
        bool yIsGreater = y > lastY;
        int start = yIsGreater ? lastY + 1 : y + 1;
        int end = yIsGreater ? y - 1 : lastY - 1;
        for (int currentY = start; currentY <= end; ++currentY) {
            if (!grid[x][currentY]->get_label().empty()) { return false; }
        }
        return true;
    } else if (sharesPathOnY) {
        bool xIsGreater = x > lastX;
        int start = xIsGreater ? lastX + 1 : x + 1;
        int end = xIsGreater ? x - 1 : lastX - 1;
        for (int currentX = start; currentX <= end; ++currentX) {
            if (!grid[currentX][y]->get_label().empty()) { return false; }
        }
        return true;
    }
    return false;
}
