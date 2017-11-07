#ifndef TP4_TALLER_MAP_H
#define TP4_TALLER_MAP_H

#define DEFAULT_HORDE_COUNT 1
#define DEFAULT_SECONDS_BEFORE_HORDE 10
#define DEFAULT_HORDE_TYPE Map::greenDemon
#define DEFAULT_SETTING Map::desert
#define DEFAULT_SIZE_X 10
#define DEFAULT_SIZE_Y 10

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
        Horde(HordeType type, int quantity, int secondsBeforeIt) :
                type(type),
                quantity(quantity),
                secondsBeforeIt(secondsBeforeIt) {}

        std::string toString(const std::string &pathName);

        HordeType type;
        int quantity;
        int secondsBeforeIt;
    };

    struct Coordinate {
        Coordinate(int x, int y) : x(x), y(y) {}
        Coordinate() : x(0), y(0) {}

        int x, y;
    };

    struct Path {
        std::vector<Coordinate> pathSequence;
        Coordinate entry;
        Coordinate exit;
        std::vector<Horde> hordes;
    };

    Map();

    void setName(const std::string &name);

    std::string getName();

    void setSetting(Map::Setting setting);

    void setSize(int width, int height);

    int getHeight();

    int getWidth();

    const std::vector<Coordinate>& getFirmGround();

    const std::vector<Path>& getPaths();

    Setting getSetting();

    std::string addHorde(Horde &horde, int pathNumber);

    void addFirmGround(int x, int y);

    std::string addEntryDoor(int x, int y);

    std::string addExitDoor(int x, int y);

    std::string addPathStep(int x, int y);

    void exportToFile(const std::string &filename) const;

    void loadFromFile(std::ifstream& source);

    static std::string toString(HordeType hordeType);

    static HordeType hordeTypeFromString(const std::string &hordeType);

private:
    static Setting settingFromString(const std::string &setting);

    static HordeType _hordeTypeFromString(const std::string &hordeType);

    std::string _toString(Setting setting) const;

    std::string _toString(HordeType hordeType) const;

    void _appendVectorOfCoordinate(const std::vector<Coordinate> &vector,
                                   YAML::Emitter &emitter) const;

    std::string name;
    Setting setting;
    Coordinate size;
    std::vector<Coordinate> firmGround;
    std::vector<Path> paths;
};


#endif //TP4_TALLER_MAP_H
