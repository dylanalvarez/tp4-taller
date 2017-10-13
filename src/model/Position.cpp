//
// Created by facundo on 10/10/17.
//

#include "Position.h"

Position::Position(float x, float y) : x(x), y(y){}

float Position::getX() const {
    return x;
}

float Position::getY() const {
    return y;
}

Position& Position::operator+=(float num) {
    this->x += num;
    this->y += num;

    return *this;
}

Position& Position::operator+=(const Position& other) {
    this->x += other.x;
    this->y += other.y;

    return *this;
}
