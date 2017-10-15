//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_POSITION_H
#define TOWERDEFENSE_POSITION_H


#include <complex>
#include <yaml-cpp/yaml.h>

class Vector {

public:
    explicit Vector(float x = 0, float y = 0);

    float getX() const;
    float getY() const;

    void set_coordinates(float x, float y);

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

    // retorna la norma del vector
    float getNorm();
private:
    float x;
    float y;
};

namespace YAML {
    template<>
    struct convert<Vector> {
        static bool decode(const Node& node, Vector& vector) {
            if(!node.IsSequence() || node.size() != 2) {
                return false;
            }
            vector.set_coordinates(node[0].as<float>(), node[1].as<float>());
            return true;
        }
    };
}



#endif //TOWERDEFENSE_POSITION_H
