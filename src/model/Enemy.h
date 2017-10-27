//
// Created by facundo on 13/10/17.
//

#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H

#include "Path.h"
#include "../../estandar_de_comunicacion/CommunicationUtils.h"

class Enemy {
public:
    Enemy(Path &path, int health_points, float speed,
          bool does_it_fly, const std::string& type = "green_demon");

    Enemy(int id, Path &path, int health_points, float speed,
          bool does_it_flight, const std::string& type = "green_demon",
          int movement_cooldown = 0);

    // mueve el enemigo la cantidad de coordenadas indicadas por speed
    // en la direccion correspondiente (segun el path)
    void move(int units_to_move = 1);

    // mueve el enemigo en la direccion opuesta a la que venia
    void moveBack();

    // reduce la vida en la cantidad indicada por dmg_points;
    // retorna los puntos de daño realizados
    unsigned int reduceLife(unsigned int dmg_points);

    // reduce la velocidad de movimiento en el porcentaje recibido
    // durante el tiempo especificado por time
    void reduceSpeed(unsigned int percentage, unsigned int time);

    bool isDead() const;

    Communication::Enemy::Type getType() const;

    // getters
    const Vector& getCurrentPosition() const;
    int getID() const;
    int getHealthPoints() const;
    float getSpeed() const;
    bool canIFlight() const;
    bool reachTheEnd() const;

private:
    Path& path;
    Vector current_pos;
    Vector current_destiny;
    Vector direction;

    const std::string type;
    int id;
    int hp;
    float speed;
    float original_speed;
    bool can_i_fly;
    // si llego al final del path
    bool i_reach_the_end;
    time_t last_speed_reduction_time;
    unsigned int speed_reduction_time;

    time_t last_moved_time;
    int movement_cooldown;
};

#endif //TOWERDEFENSE_ENEMY_H
