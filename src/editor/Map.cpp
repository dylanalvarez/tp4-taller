#include <fstream>
#include "Map.h"

#define GREEN_DEMON_STR "Demonio(s) verde(s)"
#define GOAT_MAN_STR "Hombre(s) cabra"
#define UNDEAD_STR "No muerto(s)"
#define SPECTRE_STR "Espectro(s)"
#define BLOODY_HAWK_STR "Halcon(es) sangriento(s)"
#define ABMONIBLE_STR "Abmonible(s)"

#define GREEN_DEMON_EXPORT_STR "green_demon"
#define GOAT_MAN_EXPORT_STR "goat_man"
#define UNDEAD_EXPORT_STR "undead"
#define SPECTRE_EXPORT_STR "spectre"
#define BLOODY_HAWK_EXPORT_STR "bloody_hawk"
#define ABMONIBLE_EXPORT_STR "abmonible"

#define DESERT_STR "desert"
#define VOLCANO_STR "volcano"
#define ICE_STR "ice"
#define MEADOW_STR "meadow"

void Map::_appendVectorOfCoordinate(
        const std::vector<Map::Coordinate> &vector,
        YAML::Emitter &emitter) const {
    emitter << YAML::BeginSeq;
    for (Coordinate coordinate : vector) {
        emitter << YAML::BeginMap
                << YAML::Key << "x"
                << YAML::Value << coordinate.x
                << YAML::Key << "y"
                << YAML::Value << coordinate.y
                << YAML::EndMap;
    }
    emitter << YAML::EndSeq;
}

void Map::exportToFile(const std::string &filename) const {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;

    emitter << YAML::Key << "name";
    emitter << YAML::Value << name;

    emitter << YAML::Key << "setting";
    emitter << YAML::Value << _toString(setting);

    emitter << YAML::Key << "size";
    emitter << YAML::Value << YAML::BeginMap
            << YAML::Key << "x" << YAML::Value << size.x
            << YAML::Key << "y" << YAML::Value << size.y
            << YAML::EndMap;

    emitter << YAML::Key << "firm_ground";
    emitter << YAML::Value;
    _appendVectorOfCoordinate(firmGround, emitter);

    emitter << YAML::Key << "paths";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq;
    for (const auto &path: paths) {
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "path_sequence";
        emitter << YAML::Value;
        _appendVectorOfCoordinate(path.pathSequence,
                                  emitter);
        emitter << YAML::Key << "entry";
        emitter << YAML::Value;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "x" << YAML::Value << path.entry.x;
        emitter << YAML::Key << "y" << YAML::Value << path.entry.y;
        emitter << YAML::EndMap;
        emitter << YAML::Key << "exit";
        emitter << YAML::Value;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "x" << YAML::Value << path.exit.x;
        emitter << YAML::Key << "y" << YAML::Value << path.exit.y;
        emitter << YAML::EndMap;
        emitter << YAML::Key << "enemies";
        emitter << YAML::Value;
        emitter << YAML::BeginSeq;
        for (const Horde &horde: path.hordes) {
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "type";
            emitter << YAML::Value << _toString(horde.type);
            emitter << YAML::Key << "quantity";
            emitter << YAML::Value << horde.quantity;
            emitter << YAML::Key << "seconds_before_arrival";
            emitter << YAML::Value << horde.secondsBeforeIt;
            emitter << YAML::EndMap;
        }
        emitter << YAML::EndSeq;
        emitter << YAML::EndMap;
    }
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;

    std::ofstream destination(filename);
    destination << emitter.c_str();
}

void Map::loadFromFile(std::ifstream &source) {
    YAML::Node file = YAML::Load(source);
    loadFromNode(file);
}

void Map::loadFromNode(YAML::Node& source) {
    name = source["name"].as<std::string>();
    setting = settingFromString(source["setting"].as<std::string>());
    size = Coordinate(source["size"]["x"].as<int>(), source["size"]["y"].as<int>());
    this->firmGround.clear();
    for (const YAML::Node &firmGround: source["firm_ground"]) {
        this->firmGround.emplace_back(firmGround["x"].as<int>(),
                                      firmGround["y"].as<int>());
    }
    this->paths.clear();
    YAML::Node paths = source["paths"];
    for (const YAML::Node &path : paths) {
        this->paths.emplace_back();
        for (const YAML::Node &pathStep : path["path_sequence"]) {
            this->paths.back().pathSequence.emplace_back(
                    pathStep["x"].as<int>(),
                    pathStep["y"].as<int>());
        }
        this->paths.back().entry = Map::Coordinate(
                path["entry"]["x"].as<int>(),
                path["entry"]["y"].as<int>());
        this->paths.back().exit = Map::Coordinate(
                path["exit"]["x"].as<int>(),
                path["exit"]["y"].as<int>());
        const YAML::Node &hordesAsNode = path["enemies"];
        for (const YAML::Node &hordeAsNode : hordesAsNode) {
            this->paths.back().hordes.emplace_back(
                    _hordeTypeFromString(hordeAsNode["type"].as<std::string>()),
                    hordeAsNode["quantity"].as<int>(),
                    hordeAsNode["seconds_before_arrival"].as<int>()
            );
        }
    }
}

Map::Map() : setting(DEFAULT_SETTING),
             size(DEFAULT_SIZE_X, DEFAULT_SIZE_Y) {}

std::string Map::_toString(Map::Setting setting) const {
    switch (setting) {
        case desert:
            return DESERT_STR;
        case volcano:
            return VOLCANO_STR;
        case ice:
            return ICE_STR;
        case meadow:
            return MEADOW_STR;
    }
    throw;
}

std::string Map::_toString(Map::HordeType hordeType) const {
    switch (hordeType) {
        case greenDemon:
            return GREEN_DEMON_EXPORT_STR;
        case goatMan:
            return GOAT_MAN_EXPORT_STR;
        case undead:
            return UNDEAD_EXPORT_STR;
        case spectre:
            return SPECTRE_EXPORT_STR;
        case bloodyHawk:
            return BLOODY_HAWK_EXPORT_STR;
        case abmonible:
            return ABMONIBLE_EXPORT_STR;
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

std::string Map::addHorde(Horde &horde, int pathNumber) {
    if (pathNumber <= 0 || (unsigned)pathNumber > paths.size()) {
        throw std::exception();
    }
    paths[pathNumber - 1].hordes.emplace_back(horde);
    return std::to_string(pathNumber);
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

Map::HordeType Map::hordeTypeFromString(const std::string &hordeType) {
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

Map::HordeType Map::_hordeTypeFromString(const std::string &hordeType) {
    std::map<std::string, Map::HordeType> associations{
            {GREEN_DEMON_EXPORT_STR, greenDemon},
            {GOAT_MAN_EXPORT_STR,    goatMan},
            {UNDEAD_EXPORT_STR,      undead},
            {SPECTRE_EXPORT_STR,     spectre},
            {BLOODY_HAWK_EXPORT_STR, bloodyHawk},
            {ABMONIBLE_EXPORT_STR,   abmonible},
    };
    return associations[hordeType];
}

Map::Setting Map::settingFromString(const std::string &hordeType) {
    std::map<std::string, Map::Setting> associations{
            {DESERT_STR,  desert},
            {VOLCANO_STR, volcano},
            {ICE_STR,     ice},
            {MEADOW_STR,  meadow},
    };
    return associations[hordeType];
}

void Map::setSize(int width, int height) {
    size = Coordinate(width, height);
}

void Map::addFirmGround(int x, int y) {
    firmGround.emplace_back(x, y);
}

std::string Map::addEntryDoor(int x, int y) {
    paths.emplace_back();
    paths.back().entry = Coordinate(x, y);
    return std::to_string(paths.size());
}

std::string Map::addExitDoor(int x, int y) {
    paths.back().exit = Coordinate(x, y);
    return std::to_string(paths.size());
}

std::string Map::addPathStep(int x, int y) {
    paths.back().pathSequence.emplace_back(x, y);
    return std::to_string(paths.size());
}

int Map::getWidth() {
    return size.x;
}

int Map::getHeight() {
    return size.y;
}

Map::Setting Map::getSetting() {
    return this->setting;
}

const std::vector<Map::Coordinate> &Map::getFirmGround() {
    return firmGround;
}

const std::vector<Map::Path> &Map::getPaths() {
    return paths;
}

std::string Map::Horde::toString(const std::string &pathName) {
    return "Camino " + pathName + ": " + std::to_string(this->quantity)
           + " " + Map::toString(this->type)
           + " (" + std::to_string(this->secondsBeforeIt) + " seg)";
}
