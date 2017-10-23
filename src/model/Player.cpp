//
// Created by facundo on 17/10/17.
//

#include "Player.h"

Player::Player(const std::string& name, const std::string& element) :
        name(name) {
    elements.push_back(element);
}

const std::string &Player::getName() const {
    return name;
}

Player::Player(Player&& other) noexcept {
    this->name = std::move(other.name);
}

Player &Player::operator=(Player&& other) noexcept {
    this->name = std::move(other.name);
    this->elements = std::move(other.elements);
    return *this;
}

const std::vector<std::string> &Player::getElements() const {
    return elements;
}
