#include "CommunicationUtils.h"
#include "Exception.h"

Communication::NameAndID::NameAndID() : name(), id(0) {}

Communication::NameAndID::NameAndID(const std::string &name, int id)
        : name(name), id(id) {}

std::string Communication::Upgrade::to_string(const Upgrade::Type &type) {
    std::vector<std::string> types{
            "range", "damage", "reach", "slowdown"};
    return types[type];
}

Communication::Upgrade::Upgrade(const std::string &type, int tower_id) {
    if (type == "range") { this->type = range; }
    else if (type == "reach") { this->type = reach; }
    else if (type == "damage") { this->type = damage; }
    else { this->type = slowdown; }
    this->towerID = tower_id;
}

std::string Communication::to_string(const Communication::Element &element) {
    std::vector<std::string> elements{"earth", "water", "fire", "air"};
    return elements[element];
}

std::string Communication::toFixedLengthString(long messageLength, int length) {
    std::string numberAsString = std::to_string(messageLength);
    std::string padding = std::string(
            length - numberAsString.length(), '0');
    return padding + numberAsString;
}

Communication::Element Communication::to_element(const std::string &element) {
    if (element == "fire") {
        return Communication::Element::fire;
    }
    if (element == "water") {
        return Communication::Element::water;
    }
    if (element == "air") {
        return Communication::Element::air;
    } else {
        return Communication::Element::earth;
    }
}

std::string
Communication::Enemy::to_string(const Communication::Enemy::Type &type) {
    std::vector<std::string> states{"greenDemon", "goatMan", "undead",
                                    "spectre", "bloodyHawk",
                                    "abmonible"};
    return states[type];
}

Communication::Enemy::Enemy(const std::string &type, int id, int x, int y)
        : id(id), x(x), y(y) {
    if (type == "greenDemon") { this->type = greenDemon; }
    else if (type == "goatMan") { this->type = goatMan; }
    else if (type == "undead") { this->type = undead; }
    else if (type == "spectre") { this->type = spectre; }
    else if (type == "bloodyHawk") { this->type = bloodyHawk; }
    else if (type == "abmonible") { this->type = abmonible; }
}

Communication::Enemy::Enemy(Communication::Enemy::Type type, int id, int x,
                            int y) : id(id), x(x), y(y), type(type) {}

std::string
Communication::Tower::to_string(const Communication::Tower::Type &type) {
    std::vector<std::string> states{"earth", "water", "fire", "air"};
    return states[type];
}

Communication::Tower::Tower(int id, Level level, int experience,
                            int rangeInSquares, int ExplosionRange, int x,
                            int y, Communication::Tower::EnemySlowdown slowdown,
                            Communication::Tower::Damage damage,
                            const std::string &type, bool is_attacking,
                            int current_target_id)
        : id(id), experience(experience), rangeInSquares(rangeInSquares),
          ExplosionRange(ExplosionRange), x(x), y(y), level(level),
          slowdown(slowdown), damage(damage), is_attacking(is_attacking),
          current_target_id(current_target_id) {
    if (type == "earth") { this->type = earth; }
    else if (type == "water") { this->type = water; }
    else if (type == "fire") { this->type = fire; }
    else if (type == "air") { this->type = air; }
}

Communication::Tower::Tower(int id, Level level, int experience,
                            int rangeInSquares, int ExplosionRange, int x,
                            int y, Communication::Tower::EnemySlowdown slowdown,
                            Communication::Tower::Damage damage,
                            Communication::Tower::Type type, bool is_attacking,
                            int current_target_id)
        : id(id), experience(experience), rangeInSquares(rangeInSquares),
          ExplosionRange(ExplosionRange), x(x), y(y), level(level),
          slowdown(slowdown), damage(damage), type(type),
          is_attacking(is_attacking),
          current_target_id(current_target_id) {}

Communication::Tower::Type Communication::Tower::string_to_type(
        const std::string &type) {
    if (type == "earth") { return earth; }
    else if (type == "water") { return water; }
    else if (type == "fire") { return fire; }
    else { return air; }
}

std::string Communication::PositionalPower::to_string(
        const Communication::PositionalPower::Type &type) {
    std::vector<std::string> states{"terraforming",
                                    "fissure", "fireWall", "blizzard",
                                    "tornado"};
    return states[type];
}

Communication::PositionalPower::PositionalPower(
        const std::string &type, int x, int y)
        : x(x), y(y) {
    if (type == "terraforming") { this->type = terraforming; }
    else if (type == "fissure") { this->type = fissure; }
    else if (type == "fireWall") { this->type = fireWall; }
    else if (type == "blizzard") { this->type = blizzard; }
    else if (type == "tornado") { this->type = tornado; }
}

Communication::PositionalPower::PositionalPower(
        Communication::PositionalPower::Type type, int x, int y)
        : type(type), x(x), y(y) {}

std::string Communication::TargetPower::to_string(
        const Communication::TargetPower::Type &type) {
    std::vector<std::string> states{"freezing", "ray", "meteorite"};
    return states[type];
}

Communication::TargetPower::TargetPower(const std::string &type, int enemyID)
        : enemyID(enemyID) {
    if (type == "freezing") { this->type = freezing; }
    else if (type == "ray") { this->type = ray; }
    else if (type == "meteorite") {
        this->type = Communication::TargetPower::Type::meteorite;
    }
}

Communication::TargetPower::TargetPower(
        Communication::TargetPower::Type type, int enemyID)
        : type(type), enemyID(enemyID) {}

std::string Communication::GameState::to_string(
        const Communication::GameState::State &state) {
    std::vector<std::string> states{"won", "lost", "ongoing"};
    return states[state];
}

void Communication::GameState::setState(const std::string &stateAsString) {
    if (stateAsString == "ongoing") {
        this->state = ongoing;
    } else if (stateAsString == "won") {
        this->state = won;
    } else if (stateAsString == "lost") {
        this->state = lost;
    } else {
        throw Exception("Invalid state in game state yaml: " + stateAsString);
    }
}

Communication::Tower::EnemySlowdown::EnemySlowdown(int percentage, int duration)
        : percentage(percentage), duration(duration) {}

Communication::Tower::Damage::Damage(int normal, int flying, int close_by)
        : normal(normal), flying(flying), close_by(close_by) {}

Communication::Tower::Level::Level(int range, int damage, int reach,
                                   int slowdown)
        : range(range), damage(damage), reach(reach), slowdown(slowdown) {}
