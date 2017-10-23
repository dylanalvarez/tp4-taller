//
// Created by facundo on 17/10/17.
//

#include "Player.h"

Player::Player(const std::string &name) : name(name) {}

const std::string &Player::getName() const {
    return name;
}

Player::Player(Player&& other) noexcept {
    this->name = std::move(other.name);
}

Player &Player::operator=(Player&& other) noexcept {
    this->name = std::move(other.name);
    return *this;
}
