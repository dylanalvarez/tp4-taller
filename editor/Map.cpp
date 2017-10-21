#include <fstream>
#include "Map.h"

#define GREEN_DEMON_STR "Demonio(s) verde(s)"
#define GOAT_MAN_STR "Hombre(s) cabra"
#define UNDEAD_STR "No muerto(s)"
#define SPECTRE_STR "Espectro(s)"
#define BLOODY_HAWK_STR "Halcon(es) sangriento(s)"
#define ABMONIBLE_STR "Abmonible(s)"

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

    emitter << YAML::Key << "paths";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq;
    for (const auto &path: paths) {
        _appendVectorOfCoordinate(path, emitter,
                                  [](int coord) { return 88 * coord - 44; });
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "enemies";
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

Map::Map() : setting(DEFAULT_SETTING),
             size(DEFAULT_SIZE_X, DEFAULT_SIZE_Y),
             secondsBetweenHordes(DEFAULT_SECONDS_BETWEEN_HORDES) {}

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
    throw;
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
    throw;
}

void Map::setName(const std::string &name) {
    this->name = name;
}

std::string Map::getName() {
    return this->name;
}

void Map::setSetting(Setting setting) {
    this->setting = setting;
}

void Map::setSecondsBetweenHordes(int seconds) {
    secondsBetweenHordes = seconds;
}

void Map::clearHordes() {
    hordes.clear();
}

void Map::addHorde(Horde &horde) {
    hordes.emplace_back(horde);
}

std::string Map::toString(Map::HordeType hordeType) {
    switch (hordeType) {
        case greenDemon:
            return GREEN_DEMON_STR;
        case goatMan:
            return GOAT_MAN_STR;
        case undead:
            return UNDEAD_STR;
        case spectre:
            return SPECTRE_STR;
        case bloodyHawk:
            return BLOODY_HAWK_STR;
        case abmonible:
            return ABMONIBLE_STR;
    }
    throw;
}

Map::HordeType Map::fromString(const std::string &hordeType) {
    std::map<std::string, Map::HordeType> associations{
            {GREEN_DEMON_STR, greenDemon},
            {GOAT_MAN_STR,    goatMan},
            {UNDEAD_STR,      undead},
            {SPECTRE_STR,     spectre},
            {BLOODY_HAWK_STR, bloodyHawk},
            {ABMONIBLE_STR,   abmonible},
    };
    return associations[hordeType];
}

void Map::setSize(int width, int height) {
    size = Coordinate(width, height);
}

void Map::addFirmGround(int x, int y) {
    firmGround.emplace_back(x, y);
}

void Map::addEntryDoor(int x, int y) {
    paths.emplace_back();
    entryDoors.emplace_back(x, y);
}

void Map::addExitDoor(int x, int y) {
    exitDoors.emplace_back(x, y);
}

void Map::addPathStep(int x, int y) {
    paths.back().emplace_back(x, y);
}

std::string Map::Horde::toString() {
    return std::to_string(this->quantity) + " " + Map::toString(this->type);
}
