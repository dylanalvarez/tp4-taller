//
// Created by facundo on 13/10/17.
//

#include "Enemy.h"

Enemy::Enemy(Path &path, int health_points, float speed,
             bool does_it_fly, const std::string& type) :
                    path(path),
                    current_pos(path.getInitialPosition()),
                    current_pos_number(0),
                    current_destiny(path.getNextPosition(current_pos_number++)),
                    type(type),
                    hp(health_points),
                    speed(speed * base_speed),
                    original_speed(speed * base_speed),
                    can_i_fly(does_it_fly) {
    direction = (current_destiny - current_pos);
    direction.normalizeAndRound();
    last_speed_reduction_time = 0;
    speed_reduction_time = 0;
    i_reach_the_end = false;
}

Enemy::Enemy(int id, Path &path, int health_points, float speed,
             bool does_it_fly, const std::string& type) :
        Enemy(path, health_points, speed, does_it_fly, type) {
    this->id = id;
}

void Enemy::move(int units_to_move) {
    updateSpeedReduction();
    for (int i = 0; i < getSpeed() * units_to_move; i++){
        current_pos += direction * base_speed_reduction;

        if (current_pos == current_destiny) {
            // calcula nueva direccion
            current_destiny = path.getNextPosition(current_pos_number++);
            direction = (current_destiny - current_pos);
            direction.normalizeAndRound();
        }
    }
    i_reach_the_end = (current_pos == path.getFinalPositon());
}

const Vector &Enemy::getCurrentPosition() const {
    return current_pos;
}

int Enemy::getID() const {
    return id;
}


float Enemy::getSpeed() const {
    return speed;
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

void Enemy::moveBack(int units_to_move) {
    updateSpeedReduction();
    for (int i = 0; i < getSpeed() * units_to_move; i++) {
        current_pos -= direction;
    }
}

bool Enemy::isDead() const {
    return hp == 0;
}

bool Enemy::reachTheEnd() const {
    return i_reach_the_end;
}

Communication::Enemy::Type Enemy::getType() const {
    typedef Communication::Enemy::Type enemyType;

    if (type == "green_demon") { return enemyType::greenDemon; }
    if (type == "abmonible") { return enemyType::abmonible; }
    if (type == "undead") { return enemyType::undead; }
    if (type == "bloody_hawk") { return enemyType::bloodyHawk; }
    if (type == "spectrum") { return enemyType::spectre; }
    return enemyType::goatMan;
}

void Enemy::updateSpeedReduction() {
    if (difftime(time(nullptr), last_speed_reduction_time) >=
        speed_reduction_time) { speed = original_speed; }
}
