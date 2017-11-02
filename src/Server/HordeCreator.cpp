//
// Created by facundo on 31/10/17.
//

#include "HordeCreator.h"

HordeCreator::HordeCreator(const std::string &map_file) {
    YAML::Node paths = YAML::LoadFile(map_file)["paths"];

    for (auto path = paths.begin(); path != paths.end(); ++path) {
        YAML::Node enemies = (*path)["enemies"];
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            total_amount_of_enemies += (*it)["quantity"].as<int>();
            std::string type = (*it)["type"].as<std::string>();
            Horde horde(type,
                           (*it)["time_before_arrival"].as<int>(),
                           (*it)["quantity"].as<int>());
            hordes.push(horde);
        }
    }
}

Horde HordeCreator::getNextHorde() {
    if (difftime(time(nullptr), last_horde_sended) <
            hordes.front().getTimeBeforeArrival()) { return Horde(); }

    Horde horde = hordes.front();
    hordes.pop();
    return horde;
}

void HordeCreator::start() {
    last_horde_sended = time(nullptr);
}

int HordeCreator::getTotalAmountOfEnemies() const {
    return total_amount_of_enemies;
}

HordeCreator::HordeCreator(HordeCreator&& other) noexcept {
    this->hordes = std::move(other.hordes);
    this->total_amount_of_enemies = other.total_amount_of_enemies;
}

HordeCreator& HordeCreator::operator=(HordeCreator&& other) noexcept {
    this->hordes = std::move(other.hordes);
    this->total_amount_of_enemies = other.total_amount_of_enemies;

    return *this;
}
