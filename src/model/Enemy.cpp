//
// Created by facundo on 13/10/17.
//

#include "Enemy.h"

Enemy::Enemy(Path &path, int health_points, float speed,
             bool does_it_fly) :
        path(path),
        hp(health_points),
        speed(speed),
        original_speed(speed),
        can_i_fly(does_it_fly),
        current_pos(path.getInitialPosition()),
        current_destiny(path.getNextPosition(current_pos)) {
    direction = (current_destiny - current_pos);
    direction.normalizeAndRound();
    last_speed_reduction_time = 0;
    speed_reduction_time = 0;
}

Enemy::Enemy(int id, Path &path, int health_points, float speed,
             bool does_it_fly) : Enemy(path, health_points, speed, does_it_fly) {
    this->id = id;
}

void Enemy::move() {
    for (int i = 0; i < speed; i++){
        current_pos += direction;

        if (current_pos == current_destiny){
            // calcula nueva direccion
            current_destiny = path.getNextPosition(current_destiny);
            direction = (current_destiny - current_pos);
            direction.normalizeAndRound();
        }
    }
}

const Vector &Enemy::getCurrentPosition() const {
    return current_pos;
}

int Enemy::getID() const {
    return id;
}


float Enemy::getSpeed() const {
    if (difftime(time(nullptr), last_speed_reduction_time) <
        speed_reduction_time) { return speed; }

    return original_speed;
}

bool Enemy::canIFlight() const {
    return can_i_fly;
}

int Enemy::getHealthPoints() const {
    return hp;
}

unsigned int Enemy::reduceLife(unsigned int dmg_points) {
    this->hp -= dmg_points;
    if (this->hp < 0){
        unsigned int dmg_dealed = dmg_points + hp;
        this->hp = 0;
        return dmg_dealed;
    }
    return dmg_points;
}

void Enemy::reduceSpeed(unsigned int percentage, unsigned int reduction_time) {
    this->speed -= (this->speed * percentage) / 100;

    speed_reduction_time = reduction_time;
    last_speed_reduction_time = time(nullptr);
}

void Enemy::moveBack() {
    current_pos -= direction;
}

bool Enemy::isDead() const {
    return hp == 0;
}
