#include "CommunicationUtils.h"

Communication::NameAndID::NameAndID() : name(), id(0) {}
Communication::NameAndID::NameAndID(std::string name, int id)
        : name(std::move(name)), id(id) {}

std::string Communication::Upgrade::to_string(const Upgrade::Type &type) {
    std::vector<std::string> types{
            "range", "damage", "reach", "slowdown"};
    return types[type];
}


std::string Communication::to_string(const Communication::Element &element) {
    std::vector<std::string> elements{"desert", "volcano", "ice", "meadow"};
    return elements[element];
}

std::string Communication::toFixedLengthString(long messageLength, int length) {
    std::string numberAsString = std::to_string(messageLength);
    std::string padding = std::string(
            length - numberAsString.length(), '0');
    return padding + numberAsString;
}

std::string
Communication::Enemy::to_string(const Communication::Enemy::Type &type) {
    std::vector<std::string> states{"greenDemon", "goatMan", "undead",
                                    "spectre", "bloodyHawk",
                                    "abmonible"};
    return states[type];
}

std::string
Communication::Tower::to_string(const Communication::Tower::Type &type) {
    std::vector<std::string> states{"earth", "water", "fire", "air"};
    return states[type];
}

std::string Communication::PositionalPower::to_string(
        const Communication::PositionalPower::Type &type) {
    std::vector<std::string> states{"meteorite", "terraforming",
                                    "fissure", "fireWall", "blizzard",
                                    "tornado"};
    return states[type];
}

std::string Communication::TargetPower::to_string(
        const Communication::TargetPower::Type &type) {
    std::vector<std::string> states{"freezing", "ray"};
    return states[type];
}

std::string Communication::GameState::to_string(
        const Communication::GameState::State &state) {
    std::vector<std::string> states{"won", "lost", "ongoing"};
    return states[state];
}
