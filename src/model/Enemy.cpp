//
// Created by facundo on 13/10/17.
//

#include "Enemy.h"

Enemy::Enemy(Path &path, unsigned int health_points, unsigned int speed,
             bool does_it_fly) :
        path(path),
        hp(health_points),
        speed(speed),
        can_i_fly(does_it_fly) {
    current_pos = path.getInitialPosition();
}

Enemy::Enemy(int id, Path &path, unsigned int health_points, unsigned int speed,
             bool does_it_fly) : Enemy(path, health_points, speed, does_it_fly) {
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

Enemy::Enemy(Enemy&& other) noexcept : Enemy(other.id, other.path, other.hp,
                                    other.speed, other.can_i_fly) {}

unsigned int Enemy::getSpeed() const {
    return speed;
}

unsigned int Enemy::canIFlight() const {
    return can_i_fly;
}

unsigned int Enemy::getHealthPoints() const {
    return hp;
}
