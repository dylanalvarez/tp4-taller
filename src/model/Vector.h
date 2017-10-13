//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_POSITION_H
#define TOWERDEFENSE_POSITION_H


#include <complex>

class Vector {
public:
    explicit Vector(float x = 0, float y = 0);

    float getX() const;
    float getY() const;

    Vector& operator+=(float);
    Vector& operator+=(const Vector&);
    Vector operator-(const Vector&);
    bool operator!=(const Vector&);
    bool operator==(const Vector&);
    bool operator>(const Vector&);
    Vector operator+(const Vector&);

    // divide cada coordenada por la norma del vector
    void normalize();

    // normaliza y redondea las coordenadas
    void normalizeAndRound();

private:
    float x;
    float y;
};


#endif //TOWERDEFENSE_POSITION_H
