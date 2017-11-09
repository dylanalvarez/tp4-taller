//
// Created by facundo on 31/10/17.
//

#include <iostream>
#include "HordeCreator.h"
#include "Actions/AddEnemyAction.h"

HordeCreator::HordeCreator(const std::string &map_file,
                           QueueProtected& queue) : queue(queue) {
    unsigned int path_number = 1;
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
                           (*it)["quantity"].as<int>(), path_number);
            hordes.push(horde);
        }
        path_number++;
    }
    last_horde_sended_time = 0;
    last_enemy_sended_time = 0;
}

void HordeCreator::start() {
    last_horde_sended_time = time(nullptr);
    enemies_to_send_count = hordes.front().getQuantity();
}

int HordeCreator::getTotalAmountOfEnemies() const {
    return total_amount_of_enemies;
}

void HordeCreator::addNextEnemy() {
    if (hordes.empty()) { return; }

    if (difftime(time(nullptr), last_horde_sended_time) <
        hordes.front().getTimeBeforeArrival()) { return; }

    if (difftime(time(nullptr), last_enemy_sended_time) <
        time_between_enemies) { return; }

    if (enemies_to_send_count == 0) {
        hordes.pop();
        last_horde_sended_time = time(nullptr);
        enemies_to_send_count = hordes.front().getQuantity();
    } else {
        queue.push(new AddEnemyAction(hordes.front().getType(),
                                      hordes.front().getPathNumber()));
        enemies_to_send_count--;
        last_enemy_sended_time = time(nullptr);
    }
}
