//
// Created by facundo on 13/10/17.
//

#include "Path.h"

Path::Path(std::vector<Vector>& positions) : positions(positions),
                                             current_position(positions.at(0)) {
    iterator = positions.begin();
    // calculo de primera direccion, entre el punto inicial y el siguiente
    direction = *(iterator + 1) - *iterator;
    direction.normalizeAndRound();
    iterator++;
}

const Vector &Path::getNextPosition() {
    if (iterator != positions.end()){
        current_position += direction;

        if (current_position == *iterator){
            // calcula nueva direccion
            direction = *(iterator + 1) - *iterator;
            direction.normalizeAndRound();
            iterator++;
        }
    }

    return current_position;
}

const Vector &Path::getInitialPosition() {
    return positions[0];
}
