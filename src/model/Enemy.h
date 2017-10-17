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

    // mueve el enemigo la cantidad de coordenadas indicadas por speed
    // en la direccion correspondiente (segun el path)
    void move();

    // reduce la vida en la cantidad indicada por dmg_points;
    void reduceLife(unsigned int dmg_points);

    // getters
    const Vector& getCurrentPosition() const;
    int getID() const;
    unsigned int getHealthPoints() const;
    unsigned int getSpeed() const;
    bool canIFlight() const;

    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;
    Enemy& operator=(Enemy&&) = delete;
    Enemy(Enemy&&) noexcept;

private:
    Path& path;
    Vector current_pos;
    Vector current_destiny;
    Vector direction;

    int id;
    unsigned int hp;
    unsigned int speed;
    bool can_i_fly;
};

#endif //TOWERDEFENSE_ENEMY_H
