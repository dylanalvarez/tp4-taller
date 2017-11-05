//
// Created by facundo on 31/10/17.
//

#include <iostream>
#include "HordeCreator.h"

HordeCreator::HordeCreator(const std::string &map_file) {
    total_amount_of_enemies = 0;
    YAML::Node map = YAML::LoadFile(map_file);
    YAML::Node paths = map["paths"];
    for (auto path = paths.begin(); path != paths.end(); ++path) {
        YAML::Node enemies = (*path)["enemies"];
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            total_amount_of_enemies += (*it)["quantity"].as<int>();
            std::string type = (*it)["type"].as<std::string>();
            Horde horde(type,
                           (*it)["seconds_before_arrival"].as<int>(),
                           (*it)["quantity"].as<int>());
            hordes.push(horde);
        }
    }
    last_horde_sended_time = 0;
}

Horde HordeCreator::getNextHorde() {
    if (hordes.empty()) { return Horde(); }
    if (difftime(time(nullptr), last_horde_sended_time) <
            hordes.front().getTimeBeforeArrival()) { return Horde(); }

    Horde horde = hordes.front();
    hordes.pop();
    return horde;
}

void HordeCreator::start() {
    last_horde_sended_time = time(nullptr);
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
