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

void Map::loadFromFile(std::ifstream &source) {
    YAML::Node file = YAML::Load(source);
    name = file["name"].as<std::string>();
    setting = settingFromString(file["setting"].as<std::string>());
    std::vector<int> sizeAsVector = file["size"].as<std::vector<int>>();
    size = Coordinate(sizeAsVector[0], sizeAsVector[1]);
    this->firmGround.clear();
    std::vector<std::vector<int>> firmGroundsAsVector =
            file["firm_ground"].as<std::vector<std::vector<int>>>();
    for (std::vector<int> &firmGround: firmGroundsAsVector) {
        this->firmGround.emplace_back(firmGround[0], firmGround[1]);
    }
    this->entryDoors.clear();
    std::vector<std::vector<int>> entryDoorsAsVector =
            file["doors"]["entry"].as<std::vector<std::vector<int>>>();
    for (std::vector<int> &entryDoor: entryDoorsAsVector) {
        this->entryDoors.emplace_back(entryDoor[0], entryDoor[1]);
    }
    this->exitDoors.clear();
    std::vector<std::vector<int>> exitDoorsAsVector =
            file["doors"]["exit"].as<std::vector<std::vector<int>>>();
    for (std::vector<int> &exitDoor: exitDoorsAsVector) {
        this->exitDoors.emplace_back(exitDoor[0], exitDoor[1]);
    }
    this->paths.clear();
    std::vector<std::vector<std::vector<int>>> pathsAsVector =
            file["paths"].as<std::vector<std::vector<std::vector<int>>>>();
    for (std::vector<std::vector<int>> &pathAsVector : pathsAsVector) {
        this->paths.emplace_back();
        for (std::vector<int> &pathStepAsVector : pathAsVector) {
            this->paths.back().emplace_back(
                    (pathStepAsVector[0] + 44) / 88,
                    (pathStepAsVector[1] + 44) / 88);
        }
    }
    this->hordes.clear();
    const YAML::Node& hordesAsNode = file["enemies"];
    for (const YAML::Node& hordeAsNode : hordesAsNode) {
        this->hordes.emplace_back(
                _hordeTypeFromString(hordeAsNode["type"].as<std::string>()),
                hordeAsNode["quantity"].as<int>()
        );
    }
    this->secondsBetweenHordes = file["time_between_hordes"].as<int>();
}

Map::Map() : setting(DEFAULT_SETTING),
             size(DEFAULT_SIZE_X, DEFAULT_SIZE_Y),
             secondsBetweenHordes(DEFAULT_SECONDS_BETWEEN_HORDES) {}

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

int Map::getHeight() {
    return size.y;
}

int Map::getWidth() {
    return size.x;
}

Map::Setting Map::getSetting() {
    return this->setting;
}

int Map::getSecondsBetweenHordes() {
    return secondsBetweenHordes;
}

std::string Map::Horde::toString() {
    return std::to_string(this->quantity) + " " + Map::toString(this->type);
}
