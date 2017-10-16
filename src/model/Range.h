//
// Created by facundo on 15/10/17.
//

#ifndef TOWERDEFENSE_RANGE_H
#define TOWERDEFENSE_RANGE_H


#include "Vector.h"

class Range {
public:
    Range(Vector center, float radius);

    // retorna true si el vector esta dentro de la circunferencia
    // especificada por center y radius
    bool isInRange(Vector vector) const;

private:
    Vector center;
    float radius;
};


#endif //TOWERDEFENSE_RANGE_H
