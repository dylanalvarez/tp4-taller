#include <complex>
#include "Vector.h"

Vector::Vector(float x, float y) {
    this->x = x;
    this->y = y;
}

float Vector::getX() const {
    return x;
}

float Vector::getY() const {
    return y;
}

Vector &Vector::operator+=(float num) {
    this->x += num;
    this->y += num;

    return *this;
}

Vector &Vector::operator+=(const Vector &other) {
    this->x += other.x;
    this->y += other.y;

    return *this;
}

Vector Vector::operator-(const Vector &other) const {
    return Vector(this->x - other.x, this->y - other.y);
}

void Vector::normalize() {
    double norm = std::abs(std::complex<float>(x, y));
    if (norm != 0) {
        this->x /= (int) norm;
        this->y /= (int) norm;
    }
}

bool Vector::operator!=(const Vector &other) const {
    return (this->x != other.x || this->y != other.y);
}

bool Vector::operator==(const Vector &other) const {
    return (this->x == other.x && this->y == other.y);
}

void Vector::normalizeAndRound() {
    double norm = std::abs(std::complex<float>(x, y));
    if (norm != 0) {
        this->x /= (int) norm;
        this->y /= (int) norm;
    }
}

Vector Vector::operator+(const Vector &other) const {
    return Vector(this->x + other.x, this->y + other.y);
}

bool Vector::operator>(const Vector &other) const {
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

std::string Vector::to_string() const {
    return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

Vector &Vector::operator*=(float num) {
    this->x *= num;
    this->y *= num;
    return *this;
}

Vector &Vector::operator-=(const Vector &other) {
    this->x -= other.x;
    this->y -= other.y;

    return *this;
}

Vector Vector::operator*(float num) const {
    return Vector(this->x * num, this->y * num);
}

void Vector::setCoordinatesFromTiles(float x, float y) {
    if (x == 0) { this->x = 0; }
    else { this->x = x * 88 - 44; }
    if (y == 0) { this->y = 0; }
    else { this->y = y * 88 - 44; }

    this->x = std::roundf(this->x);
    this->y = std::roundf(this->y);
}
