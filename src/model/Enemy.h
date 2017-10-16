//
// Created by facundo on 13/10/17.
//

#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H

#include "Path.h"

class Enemy {
public:
    Enemy(Path &path, unsigned int health_points, unsigned int speed,
          bool does_it_fly);

    Enemy(int id, Path &path, unsigned int health_points, unsigned int speed,
          bool does_it_flight);

    // mueve el enemigo las coordenadas indicadas por speed
    // en la direccion correspondiente
    void move();

    // getters
    const Vector& getCurrentPosition() const;
    int getID() const;
    unsigned int getHealthPoints() const;
    unsigned int getSpeed() const;
    unsigned int canIFlight() const;

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
    bool can_i_fly;
};

#endif //TOWERDEFENSE_ENEMY_H