//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_HORDECREATOR_H
#define TOWERDEFENSE_HORDECREATOR_H

#include <string>
#include <queue>
#include "../model/Enemy.h"
#include "Horde.h"

class HordeCreator {
public:
    explicit HordeCreator(const std::string& map_file);

    // comienza a contar los segundos para la primera horda
    void start();

    // retorna la siguiente horda, segun esta especificado en el yaml del mapa
    Horde getNextHorde();

    int getTotalAmountOfEnemies() const;

    HordeCreator(const HordeCreator&) = delete;
    HordeCreator& operator=(const HordeCreator&) = delete;
    HordeCreator(HordeCreator&&) noexcept ;
    HordeCreator& operator=(HordeCreator&&) noexcept ;

private:
    std::queue<Horde> hordes;
    int total_amount_of_enemies;

    time_t last_horde_sended;
};


#endif //TOWERDEFENSE_HORDECREATOR_H
