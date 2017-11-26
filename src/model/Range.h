#ifndef TOWERDEFENSE_RANGE_H
#define TOWERDEFENSE_RANGE_H


#include "Vector.h"

class Range {
public:
    explicit Range(Vector center = Vector(0, 0), float radius = 0);

    // retorna true si el vector esta dentro de la circunferencia
    // especificada por center y radius
    bool isInRange(Vector vector) const;

    float getRadius() const;

    // retorna el radio teorico, sin ajustar a los tiles
    int getNormalRadius() const;

    Vector getCenter() const;

private:
    Vector center;
    float radius;
};


#endif //TOWERDEFENSE_RANGE_H
