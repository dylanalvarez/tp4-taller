//
// Created by facundo on 15/10/17.
//

#include "Range.h"

Range::Range(Vector center, float radius) : center(center), radius(radius) {}

bool Range::isInRange(Vector vector) const {
    return ((vector - center).getNorm() <= radius);
}

float Range::getRadius() const {
    return radius;
}

Vector Range::getCenter() const {
    return center;
}
