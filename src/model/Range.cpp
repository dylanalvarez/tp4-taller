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

int Range::getNormalRadius() const {
    return (int) std::round(radius + 44) / 88;
}
