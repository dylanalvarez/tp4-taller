//
// Created by facundo on 10/10/17.
//

#include <complex>
#include "Vector.h"

Vector::Vector(float x, float y) : x(x), y(y){}

float Vector::getX() const {
    return x;
}

float Vector::getY() const {
    return y;
}

Vector& Vector::operator+=(float num) {
    this->x += num;
    this->y += num;

    return *this;
}

Vector& Vector::operator+=(const Vector& other) {
    this->x += other.x;
    this->y += other.y;

    return *this;
}

Vector Vector::operator-(const Vector& other) {
    return Vector(this->x - other.x, this->y - other.y);
}

void Vector::normalize() {
    double norm = std::abs(std::complex<float>(x, y));
    this->x /= norm;
    this->y /= norm;
}

bool Vector::operator!=(const Vector& other) {
    return (this->x != other.x || this->y != other.y);
}

bool Vector::operator==(const Vector& other) {
    return (this->x == other.x && this->y == other.y);
}

void Vector::normalizeAndRound() {
    double norm = std::abs(std::complex<float>(x, y));
    this->x /= (int)norm;
    this->y /= (int)norm;
}

Vector Vector::operator+(const Vector& other) {
    return Vector(this->x + other.x, this->y + other.y);
}

bool Vector::operator>(const Vector& other) {
    double my_norm = std::abs(std::complex<float>(x, y));
    double other_norm = std::abs(std::complex<float>(other.x, other.y));

    return my_norm > other_norm;
}

void Vector::set_coordinates(float x, float y) {
    this->x = x;
    this->y = y;
}

float Vector::getNorm() {
    return std::abs(std::complex<float>(x, y));
}
