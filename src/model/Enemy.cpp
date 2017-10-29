//
// Created by facundo on 13/10/17.
//

#include "Enemy.h"

Enemy::Enemy(Path &path, int health_points, float speed,
             bool does_it_fly, const std::string& type) :
                                                path(path),
                                                current_pos(path.getInitialPosition()),
                                                current_destiny(path.getNextPosition(current_pos)),
                                                type(type),
                                                hp(health_points),
                                                speed(speed * pixels_per_unit),
                                                original_speed(speed),
                                                can_i_fly(does_it_fly) {
    direction = (current_destiny - current_pos);
    direction.normalizeAndRound();
    last_speed_reduction_time = 0;
    last_moved_time = 0;
    speed_reduction_time = 0;
    i_reach_the_end = false;
}

Enemy::Enemy(int id, Path &path, int health_points, float speed,
             bool does_it_fly, const std::string& type, int movement_cooldown) :
        Enemy(path, health_points, speed, does_it_fly, type) {
    this->id = id;
    this->movement_cooldown = movement_cooldown;
}

void Enemy::move(int units_to_move) {
    if (difftime(time(nullptr), last_moved_time) < movement_cooldown) {
        return;
    }

    for (int i = 0; i < getSpeed() * units_to_move; i++){
        current_pos += direction;

        if (current_pos == current_destiny){
            // calcula nueva direccion
            current_destiny = path.getNextPosition(current_destiny);
            direction = (current_destiny - current_pos);
            direction.normalizeAndRound();
        }
    }
    if (current_pos == path.getFinalPositon()) { i_reach_the_end = true; }
    last_moved_time = time(nullptr);
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
