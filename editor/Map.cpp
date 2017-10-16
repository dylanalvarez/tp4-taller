#include <fstream>
#include "Map.h"

void Map::_appendVectorOfCoordinate(
        const std::vector<Map::Coordinate> &vector,
        YAML::Emitter &emitter,
        const std::function<int(int)> &transformation) const {
    emitter << YAML::BeginSeq;
    for (Coordinate coordinate : vector) {
        emitter << YAML::BeginSeq
                << transformation(coordinate.x) << transformation(coordinate.y)
                << YAML::EndSeq;
    }
    emitter << YAML::EndSeq;
}

void Map::_appendVectorOfCoordinate(const std::vector<Map::Coordinate> &vector,
                                    YAML::Emitter &emitter) const {
    _appendVectorOfCoordinate(vector, emitter, [](int coord) { return coord; });
}

void Map::exportToFile(const std::string &filename) const {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;

    emitter << YAML::Key << "name";
    emitter << YAML::Value << name;

    emitter << YAML::Key << "setting";
    emitter << YAML::Value << _toString(setting);

    emitter << YAML::Key << "size";
    emitter << YAML::Value
            << YAML::BeginSeq << size.x << size.y << YAML::EndSeq;

    emitter << YAML::Key << "firm_ground";
    emitter << YAML::Value;
    _appendVectorOfCoordinate(firmGround, emitter);

    emitter << YAML::Key << "doors";
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "entry";
    emitter << YAML::Value;
    _appendVectorOfCoordinate(entryDoors, emitter);
    emitter << YAML::Key << "exit";
    emitter << YAML::Value;
    _appendVectorOfCoordinate(exitDoors, emitter);
    emitter << YAML::EndMap;

    emitter << YAML::Key << "path";
    emitter << YAML::Value;
    _appendVectorOfCoordinate(path, emitter,
                              [](int coord) { return 88 * coord - 44; });

    emitter << YAML::Key << "hordes";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq;
    for (Horde horde: hordes) {
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "type";
        emitter << YAML::Value << _toString(horde.type);
        emitter << YAML::Key << "quantity";
        emitter << YAML::Value << horde.quantity;
        emitter << YAML::EndMap;
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "time_between_hordes";
    emitter << YAML::Value << secondsBetweenHordes;

    emitter << YAML::EndMap;

    std::ofstream destination(filename);
    destination << emitter.c_str();
}

Map::Map() : name(""),
             setting(desert),
             size(10, 10),
             secondsBetweenHordes(10) {}

std::string Map::_toString(Map::Setting setting) const {
    switch (setting) {
        case desert:
            return "desert";
        case volcano:
            return "volcano";
        case ice:
            return "ice";
        case meadow:
            return "meadow";
    }
}

std::string Map::_toString(Map::HordeType hordeType) const {
    switch (hordeType) {
        case greenDemon:
            return "green_demon";
        case goatMan:
            return "goat_man";
        case undead:
            return "undead";
        case spectre:
            return "spectre";
        case bloodyHawk:
            return "bloody_hawk";
        case abmonible:
            return "abmonible";
    }
}

void Map::setName(const std::string &name) {
    this->name = name;
}

void Map::setSetting(Setting setting) {
    this->setting = setting;
}

void Map::setSecondsBetweenHordes(int seconds) {
    secondsBetweenHordes = seconds;
}
