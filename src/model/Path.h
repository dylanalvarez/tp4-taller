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

    // devuelve la siguiente posicion
    const Vector& getNextPosition(unsigned long actual_index);

    const Vector& getInitialPosition() const;
    const Vector& getFinalPosition() const;
    unsigned long getFinalPositionIndex() const;

    // las posiciones son centro de tiles
    // retorna true si position esta en el camino de un tile a otro
    bool containsPosition(const Vector& position);

    Path(const Path&) = delete;
    Path& operator=(const Path&) = delete;
    Path(Path&&) noexcept;
    Path& operator=(Path&&) noexcept;

private:
    std::vector<Vector> positions;
};

#endif //TOWERDEFENSE_PATH_H
