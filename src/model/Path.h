//
// Created by facundo on 13/10/17.
//

#ifndef TOWERDEFENSE_PATH_H
#define TOWERDEFENSE_PATH_H

#include <vector>
#include "Vector.h"

class Path {
public:
    // recibe una lista de posiciones que indican el centro de un tile
    explicit Path(std::vector<Vector>&&);

    // devuelve la siguiente posicion en la direccion adecuada
    const Vector& getNextPosition(const Vector& actual);

    const Vector& getInitialPosition();

    bool containsPosition(const Vector& position);

    Path(const Path&) = delete;
    Path& operator=(const Path&) = delete;
    Path(Path&&) noexcept;
    Path& operator=(Path&&) noexcept;

private:
    std::vector<Vector> positions;
};

#endif //TOWERDEFENSE_PATH_H
