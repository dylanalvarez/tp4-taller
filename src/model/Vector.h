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

    void setCoordinatesFromTiles(float x, float y);

    // sobrecarga de operadores
    Vector &operator+=(float);

    Vector &operator+=(const Vector &);

    Vector &operator-=(const Vector &);

    Vector operator-(const Vector &) const;

    bool operator!=(const Vector &) const;

    bool operator==(const Vector &) const;

    bool operator>(const Vector &) const;

    Vector operator+(const Vector &) const;

    Vector &operator*=(float);

    Vector operator*(float) const;

    // divide cada coordenada por la norma del vector
    void normalize();

    // normaliza y redondea las coordenadas
    void normalizeAndRound();

    // retorna la norma del vector
    float getNorm();

    std::string to_string() const;

private:
    float x;
    float y;
};

namespace YAML {
    template<>
    struct convert<Vector> {
        static bool decode(const Node &node, Vector &vector) {
            if (!node.IsMap() || node.size() != 2) {
                return false;
            }
            vector.setCoordinatesFromTiles(node["x"].as<float>(),
                                           node["y"].as<float>());
            return true;
        }
    };
}

#endif //TOWERDEFENSE_POSITION_H
