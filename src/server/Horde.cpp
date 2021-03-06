#include "Horde.h"

Horde::Horde(std::string &type, int time_before_arrival, int quantity,
             unsigned int path_number) {
    this->type = std::move(type);
    this->time_before_arrival = time_before_arrival;
    this->quantity = quantity;
    this->path_number = path_number;
}

Horde::Horde() {
    this->type = "";
    this->time_before_arrival = 0;
    this->quantity = 0;
}

int Horde::getTimeBeforeArrival() const {
    return time_before_arrival;
}

int Horde::getQuantity() const {
    return quantity;
}

const std::string &Horde::getType() const {
    return type;
}

unsigned int Horde::getPathNumber() const {
    return path_number;
}
