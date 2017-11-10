//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_HORDECREATOR_H
#define TOWERDEFENSE_HORDECREATOR_H

#include <string>
#include <queue>
#include "../model/Enemy.h"
#include "Horde.h"
#include "QueueProtected.h"

#define time_between_enemies 3 // segundos

class HordeCreator {
public:
    explicit HordeCreator(const std::string& map_file, QueueProtected& queue);

    // comienza a contar los segundos para la primera horda
    void start();

    // retorna la siguiente horda, segun esta especificado en el yaml del mapa
    void addNextEnemy();

    int getTotalAmountOfEnemies() const;

    HordeCreator(const HordeCreator&) = delete;
    HordeCreator& operator=(const HordeCreator&) = delete;

private:
    std::queue<Horde> hordes;
    int total_amount_of_enemies;

    time_t last_horde_sended_time;
    time_t last_enemy_sended_time;
    int enemies_to_send_count;
    QueueProtected& queue;
};


#endif //TOWERDEFENSE_HORDECREATOR_H
