//
// Created by facundo on 13/10/17.
//

#include "Path.h"

Path::Path(std::vector<Vector>& positions) : positions(positions),
                                             current_position(positions.at(0)) {
    current_index = 0;
    direction = positions.at(current_index + 1) - positions.at(current_index);
    direction.normalizeAndRound();
    current_index++;
}

const Vector &Path::getNextPosition() {
    if (current_position != positions.back()){
        if ((current_position + direction) > positions.back()){
            // si se va mas alla de la ultima posicion, dejar en la ultima
            current_position = positions.back();
        } else {
            current_position += direction;
        }

        if (current_position == positions.at(current_index)){
            // calcula nueva direccion
            direction = positions[current_index + 1] - positions[current_index];
            direction.normalizeAndRound();
            current_index++;
        }
    }

    return current_position;
}

const Vector &Path::getInitialPosition() {
    return positions[0];
}
