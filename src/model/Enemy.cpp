//
// Created by facundo on 13/10/17.
//

#include "Enemy.h"

Enemy::Enemy(Path &path, unsigned int health_points, unsigned int speed,
             bool does_it_fly) :
        path(path),
        hp(health_points),
        speed(speed),
        can_i_fly(does_it_fly),
        current_pos(path.getInitialPosition()),
        current_destiny(path.getNextPosition(current_pos)) {
    direction = (current_destiny - current_pos);
    direction.normalizeAndRound();
}

Enemy::Enemy(int id, Path &path, unsigned int health_points, unsigned int speed,
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

Enemy::Enemy(Enemy&& other) noexcept : Enemy(other.id, other.path, other.hp,
                                    other.speed, other.can_i_fly) {}

unsigned int Enemy::getSpeed() const {
    return speed;
}

bool Enemy::canIFlight() const {
    return can_i_fly;
}

unsigned int Enemy::getHealthPoints() const {
    return hp;
}

void Enemy::reduceLife(unsigned int dmg_points) {
    this->hp -= dmg_points;
}
