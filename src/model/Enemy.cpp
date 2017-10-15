//
// Created by facundo on 13/10/17.
//

#include "Enemy.h"

Enemy::Enemy(Path &path, unsigned int health_points, unsigned int speed,
             bool does_it_flight) :
        path(path),
        hp(health_points),
        speed(speed),
        can_i_flight(does_it_flight) {
    current_pos = path.getInitialPosition();
}

Enemy::Enemy(int id, Path &path, unsigned int health_points, unsigned int speed,
             bool does_it_flight) : Enemy(path, health_points, speed, does_it_flight) {
    this->id = id;
}


void Enemy::move() {
    for (int i = 0; i < speed; i++){
        current_pos = path.getNextPosition();
    }
}

const Vector &Enemy::getCurrentPosition() const {
    return current_pos;
}

int Enemy::getID() const {
    return id;
}

bool Enemy::isValid() const {
    return true;
}

Enemy::Enemy(Enemy&& other) : Enemy(other.id, other.path, other.hp,
                                    other.speed, other.can_i_flight) {}
