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

void Enemy::move() {
    for (int i = 0; i < speed; i++){
        current_pos = path.getNextPosition();
    }
}

const Vector &Enemy::getCurrentPosition() const {
    return current_pos;
}
