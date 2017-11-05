//
// Created by facundo on 31/10/17.
//

#include "Horde.h"

Horde::Horde(std::string &type, int time_before_arrival, int quantity) {
    this->type = std::move(type);
    this->time_before_arrival = time_before_arrival;
    this->quantity = quantity;
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
