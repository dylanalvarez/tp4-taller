#ifndef TP4_TALLER_MAP_H
#define TP4_TALLER_MAP_H

#define DEFAULT_HORDE_COUNT 1
#define DEFAULT_HORDE_TYPE Map::greenDemon
#define DEFAULT_SETTING Map::desert
#define DEFAULT_SIZE_X 10
#define DEFAULT_SIZE_Y 10
#define DEFAULT_SECONDS_BETWEEN_HORDES 10

#include <yaml-cpp/yaml.h>

class Map {
public:
    enum Setting {
        desert, volcano, ice, meadow
    };
    enum HordeType {
        greenDemon, goatMan, undead, spectre, bloodyHawk, abmonible
    };

    struct Horde {
        Horde(HordeType type, int quantity) : type(type), quantity(quantity) {}

        std::string to_string();

        HordeType type;
        int quantity;
    };

    Map();

    void setName(const std::string &name);

    void setSetting(Map::Setting setting);

    void setSecondsBetweenHordes(int seconds);

    void addHorde(Horde &horde);

    void clearHordes();

    void exportToFile(const std::string &filename) const;

private:
    struct Coordinate {
        Coordinate(int x, int y) : x(x), y(y) {}

        int x, y;
    };

    std::string _toString(Setting setting) const;

    std::string _toString(HordeType hordeType) const;

    void _appendVectorOfCoordinate(const std::vector<Coordinate> &vector,
                                   YAML::Emitter &emitter) const;

    void _appendVectorOfCoordinate(
            const std::vector<Coordinate> &vector,
            YAML::Emitter &emitter,
            const std::function<int(int)> &transformation) const;

    std::string name;
    Setting setting;
    Coordinate size;
    std::vector<Coordinate> firmGround;
    std::vector<Coordinate> entryDoors;
    std::vector<Coordinate> exitDoors;
    std::vector<Coordinate> path;
    std::vector<Horde> hordes;
    int secondsBetweenHordes;
};


#endif //TP4_TALLER_MAP_H
