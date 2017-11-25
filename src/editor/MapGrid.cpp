#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include "MapGrid.h"

MapGrid::MapGrid(Map &map,
                 Builder &builder,
                 int width,
                 int height,
                 SaveButton *saveButton,
                 AddHordeGrid *addHordeGrid) :
        builder(builder), squareType(start), width(width), height(height),
        lastPathX(-1), lastPathY(-1), startX(-1), startY(-1),
        unfinishedPath(false), justStartedPath(false), map(map),
        saveButton(saveButton), addHordeGrid(addHordeGrid) {
    for (int x = 0; x <= width + 1; x++) {
        grid.emplace_back();
        for (int y = 0; y <= height + 1; y++) {
            auto square = Gtk::manage(new MapButton("", x, y, *this, map));
            attach(*square, x, y, 1, 1);
            square->show();
            grid[x].push_back(square);
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
    this->builder.get_widget("delete-path", deletePathButton);
    deletePathButton->join_group(*startButton);
    this->builder.get_widget("delete-firm-ground", deleteFirmGroundButton);
    deleteFirmGroundButton->join_group(*startButton);

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
    deletePathButton->signal_clicked().connect(
            sigc::bind<MapGrid::SquareType>(
                    sigc::mem_fun(this, &MapGrid::setSquareType),
                    MapGrid::deletePath));
    deleteFirmGroundButton->signal_clicked().connect(
            sigc::bind<MapGrid::SquareType>(
                    sigc::mem_fun(this, &MapGrid::setSquareType),
                    MapGrid::deleteFirmGround));

    colors.emplace_back("rgb(255,0,0)");
    colors.emplace_back("rgb(128,255,0)");
    colors.emplace_back("rgb(0,255,255)");
    colors.emplace_back("rgb(127,0,255)");
    colors.emplace_back("rgb(255,0,127)");
    colors.emplace_back("rgb(255,255,0)");

    // Set default value
    startButton->set_active(true);
    this->updateButtons();
}

void MapGrid::setFromMap() {
    for (auto& column : grid) {
        for (auto& button : column) {
            button->set_sensitive(true);
            button->set_label("");
        }
    }
    for (const Map::Coordinate &firmGround : map.getFirmGround()) {
        grid[firmGround.x][firmGround.y]->set_label(FIRM_GROUND_STR);
    }
    int pathNumber = 1;
    for (const Map::Path &path : map.getPaths()) {
        std::string pathLabel = std::to_string(pathNumber);
        grid[path.entry.x][path.entry.y]->set_label(ENTRY_DOOR_STR + pathLabel);
        if (!(path.exit.x == 0 && path.exit.y == 0))
            grid[path.exit.x][path.exit.y]->set_label(EXIT_DOOR_STR + pathLabel);
        int stepNumber = 1;
        for (const Map::Coordinate &pathStep : path.pathSequence) {
            grid[pathStep.x][pathStep.y]->set_label(std::to_string(stepNumber));
            stepNumber++;
        }
        pathNumber++;
    }
    updateButtons();
}

void MapGrid::setSquareType(MapGrid::SquareType squareType) {
    this->squareType = squareType;
    this->updateButtons();
}

MapGrid::SquareType MapGrid::getSquareType() const {
    return squareType;
}

void MapGrid::updateButtons() const {
    saveButton->set_sensitive(!unfinishedPath &&
                              !map.getName().empty());
    for (int x = 0; x <= width + 1; x++) {
        for (int y = 0; y <= height + 1; y++) {
            updateDisabledButton(x, y);
        }
    }
    updateButtonColors();
}

void MapGrid::updateDisabledButton(int x, int y) const {
    Gtk::Button *button = grid[x][y];
    button->set_sensitive(!(shouldBeDisabled(x, y)));
}

bool MapGrid::shouldBeDisabled(int x, int y) const {
    bool isMarked = !grid[x][y]->get_label().empty();
    if (isMarked
        && !(squareType == deletePath || squareType == deleteFirmGround)) {
        return true;
    }

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
             unfinishedPath &&
             (isNeighbourOfStart(x, y) || !justStartedPath) &&
             isOnStraightLineFromLastOne(x, y)) ||
            (squareType == deletePath &&
             isStart(x, y)) ||
            (squareType == deleteFirmGround &&
             isFirmGround(x, y)) ||
            (squareType == firmGround &&
             !isOnTheEdge &&
             !isNeighbourOfStart(x, y) &&
             !isOnTheWayOfAPath(x, y));

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
        map.addPathStep(x, y);
        grid[x][y]->set_label(std::to_string(
                map.getPaths().back().pathSequence.size()));

        this->lastPathX = x;
        this->lastPathY = y;
        justStartedPath = false;
    }
    if (squareType == deletePath) {
        addHordeGrid->setFromMap();
        this->setFromMap();
        if (unfinishedPath && startX == x && startY == y) {
            unfinishedPath = false;
            justStartedPath = false;
            lastPathX = -1;
            lastPathY = -1;
            startX = -1;
            startY = -1;
        }
    }
    if (squareType == deleteFirmGround) {
        addHordeGrid->setFromMap();
        this->setFromMap();
    }
    this->updateButtons();
}

bool MapGrid::isNeighbourOfStart(int x, int y) const {
    return isStart(x - 1, y) ||
           isStart(x, y - 1) ||
           isStart(x + 1, y) ||
           isStart(x, y + 1);
}

bool MapGrid::isStart(int x, int y) const {
    return grid[x][y]->get_label().substr(0, 1) == ENTRY_DOOR_STR;
}

bool MapGrid::isOnStraightLineFromLastOne(int x, int y) const {
    int lastX = lastPathX == -1 ? startX : lastPathX;
    int lastY = lastPathY == -1 ? startY : lastPathY;
    return x == lastX || y == lastY;
}

bool MapGrid::isOnTheWayOfAPath(int x, int y) const {
    for (auto &mapPath : map.getPaths()) {
        auto lastStep = mapPath.entry;
        for (auto& step : mapPath.pathSequence) {
            if (lastStep.x == step.x){
                int start = lastStep.y < step.y ? lastStep.y : step.y;
                int end = lastStep.y < step.y ? step.y : lastStep.y;
                for (int currentY = start; currentY<= end; currentY++) {
                    if(y == currentY && x == step.x) { return true; }
                }
            } else {
                int start = lastStep.x < step.x ? lastStep.x : step.x;
                int end = lastStep.x < step.x ? step.x : lastStep.x;
                for (int currentX = start; currentX<= end; currentX++) {
                    if(x == currentX && y == step.y) { return true; }
                }
            }
            lastStep = step;
        }
    }
    return false;
}

void MapGrid::updateButtonColors() const {
    int pathIndex = 0;
    for (auto& path : map.getPaths()) {
        auto& color = colors[pathIndex % colors.size()];
        grid[path.entry.x][path.entry.y]->setColor(color);
        if (!(path.exit.x == 0 && path.exit.y == 0)) {
            grid[path.exit.x][path.exit.y]->setColor(color);
        }
        const Map::Coordinate* previousStep = nullptr;
        for (auto& pathStep : path.pathSequence) {
            if (previousStep) {
                paintBetween(*previousStep, pathStep, color);
            } else {
                paintBetween(pathStep, pathStep, color);
            }
            previousStep = &pathStep;
        }
        pathIndex++;
    }
    for (auto& firmGround : map.getFirmGround()) {
        grid[firmGround.x][firmGround.y]->setColor(
                Gdk::RGBA("black"));
    }
}

void MapGrid::paintBetween(const Map::Coordinate &start,
                           const Map::Coordinate &end,
                           const Gdk::RGBA &color) const {
    bool sharesPathOnX = end.x == start.x;
    bool sharesPathOnY = end.y == start.y;
    if (sharesPathOnX) {
        bool yIsGreater = end.y > start.y;
        int startY = yIsGreater ? start.y : end.y;
        int endY = yIsGreater ? end.y : start.y;
        for (int currentY = startY; currentY <= endY; ++currentY) {
            grid[start.x][currentY]->setColor(color);
        }
    } else if (sharesPathOnY) {
        bool xIsGreater = end.x > start.x;
        int startX = xIsGreater ? start.x : end.x;
        int endX = xIsGreater ? end.x : start.x;
        for (int currentX = startX; currentX <= endX; ++currentX) {
            grid[currentX][start.y]->setColor(color);
        }
    }
}

bool MapGrid::isFirmGround(int x, int y) const {
    return grid[x][y]->get_label().substr(0, 1) == FIRM_GROUND_STR;
}
