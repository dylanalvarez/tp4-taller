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
    explicit Path(std::vector<Vector>);

    // devuelve la siguiente posicion en la direccion adecuada
    const Vector& getNextPosition();

    const Vector& getInitialPosition();

    Path(const Path&) = delete;
    Path& operator=(const Path&) = delete;
    Path(Path&&);
    Path& operator=(Path&&);

private:
    std::vector<Vector> positions;
    Vector current_position;
    Vector direction;
    std::vector<Vector>::iterator iterator;
};

#endif //TOWERDEFENSE_PATH_H
