//
// Created by facundo on 13/10/17.
//

#include "Path.h"

Path::Path(std::vector<Vector>&& positions) : positions(std::move(positions)) {}

const Vector &Path::getNextPosition(const Vector& actual) {
    for (unsigned int i = 0; i < positions.size() - 1; i++){
        if (positions[i] == actual){
            return positions[i + 1];
        }
    }
    return positions.back();
}

const Vector &Path::getInitialPosition() const {
    return positions[0];
}

Path::Path(Path&& other) noexcept {
    this->positions = std::move(other.positions);
}

Path &Path::operator=(Path&& other) noexcept {
    this->positions = std::move(other.positions);
    return *this;
}

bool Path::containsPosition(const Vector &position) {
    for (unsigned int i = 0; i < positions.size() - 1; i++) {
        Vector direction = positions[i + 1] - positions[i];
        direction.normalizeAndRound();
        Vector initial = positions[i];
        while (initial != positions[i + 1]) {
            if (initial == position) { return true; }
            initial += direction;
        }
    }
    return false;
}

const Vector &Path::getFinalPositon() const {
    return positions.back();
}
