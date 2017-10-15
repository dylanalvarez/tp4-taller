#ifndef TP4_TALLER_MAP_H
#define TP4_TALLER_MAP_H


#include <yaml-cpp/yaml.h>

class Map {
public:
    Map();

    void exportToFile(std::string filename);

private:
    enum Setting {
        desert, volcano, ice, meadow
    };
    enum HordeType {
        greenDemon, goatMan, undead, spectre, bloodyHawk, abmonible
    };

    struct Coordinate {
        Coordinate(int x, int y) : x(x), y(y) {}

        int x, y;
    };

    struct Horde {
        Horde(HordeType type, int quantity) : type(type), quantity(quantity) {}

        HordeType type;
        int quantity;
    };

    std::string _toString(Setting setting);

    std::string _toString(HordeType hordeType);

    void _appendVectorOfCoordinate(const std::vector<Coordinate> &vector,
                                   YAML::Emitter &emitter);

    void _appendVectorOfCoordinate(
            const std::vector<Coordinate> &vector,
            YAML::Emitter &emitter,
            const std::function<int(int)> &transformation);

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
