//
// Created by facundo on 13/10/17.
//

#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H

#include "Path.h"

class Enemy {
public:
    Enemy(Path &path, unsigned int health_points, unsigned int speed,
          bool does_it_flight);

    Enemy(int id, Path &path, unsigned int health_points, unsigned int speed,
          bool does_it_flight);

    // mueve el enemigo las coordenadas indicadas por speed
    // en la direccion correspondiente
    void move();

    const Vector& getCurrentPosition() const;

    int getID() const;

    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;
    Enemy& operator=(Enemy&&) = delete;
    Enemy(Enemy&&) noexcept;

private:
    int id;
    Path& path;
    Vector current_pos;
    unsigned int hp;
    unsigned int speed;
    bool can_i_flight;
};

#endif //TOWERDEFENSE_ENEMY_H
