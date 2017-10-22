//
// Created by facundo on 13/10/17.
//

#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H

#include "Path.h"

class Enemy {
public:
    Enemy(Path &path, unsigned int health_points, float speed,
          bool does_it_fly);

    Enemy(int id, Path &path, unsigned int health_points, float speed,
          bool does_it_flight);

    // mueve el enemigo la cantidad de coordenadas indicadas por speed
    // en la direccion correspondiente (segun el path)
    void move();

    // mueve el enemigo en la direccion opuesta a la que venia
    void move_back();

    // reduce la vida en la cantidad indicada por dmg_points;
    void reduceLife(unsigned int dmg_points);

    // reduce la velocidad de movimiento en el porcentaje recibido
    // durante el tiempo especificado por time
    void reduceSpeed(unsigned int percentage, unsigned int time);

    // getters
    const Vector& getCurrentPosition() const;
    int getID() const;
    unsigned int getHealthPoints() const;
    float getSpeed() const;
    bool canIFlight() const;

private:
    Path& path;
    Vector current_pos;
    Vector current_destiny;
    Vector direction;

    int id;
    unsigned int hp;
    float speed;
    float original_speed;
    bool can_i_fly;
    time_t last_speed_reduction_time;
    unsigned int speed_reduction_time;
};

#endif //TOWERDEFENSE_ENEMY_H
