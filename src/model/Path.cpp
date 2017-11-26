#include "Path.h"

Path::Path(std::vector<Vector> &&positions) : positions(std::move(positions)) {}

const Vector &Path::getNextPosition(unsigned long actual_index) {
    if (actual_index >= positions.size() - 1) { return positions.back(); }
    return positions.at(actual_index + 1);
}

const Vector &Path::getInitialPosition() const {
    return positions[0];
}

Path::Path(Path &&other) noexcept {
    this->positions = std::move(other.positions);
}

Path &Path::operator=(Path &&other) noexcept {
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

const Vector &Path::getFinalPosition() const {
    return positions.back();
}

unsigned long Path::getFinalPositionIndex() const {
    return positions.size() - 1;
}
