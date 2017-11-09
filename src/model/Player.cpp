//
// Created by facundo on 17/10/17.
//

#include <algorithm>
#include <utility>
#include "Player.h"

Player::Player(std::string name, std::string element) :
        name(std::move(name)) {
    elements.emplace_back(element);
}

Player::Player(std::string name) : name(std::move(name)) {}

const std::string &Player::getName() const {
    return name;
}

Player::Player(Player&& other) noexcept {
    this->name = std::move(other.name);
    this->elements = std::move(other.elements);
    this->towers = std::move(other.towers);
}

Player &Player::operator=(Player&& other) noexcept {
    this->name = std::move(other.name);
    this->elements = std::move(other.elements);
    this->towers = std::move(other.towers);
    return *this;
}

const std::vector<std::string> &Player::getElements() const {
    return elements;
}

void Player::addTower(const Tower& tower) {
    towers.push_back(&tower);
}

bool Player::containsTower(const Tower& tower) const {
    return (std::find(towers.begin(), towers.end(), &tower) != 
            towers.end());
}

bool Player::canBuildTower(const std::string &type) const {
    return (std::find(elements.begin(), elements.end(), type) !=
            elements.end());
}

const std::vector<const Tower*> Player::getTowers() const {
    return towers;
}

void Player::addElement(const std::string &element) {
    elements.push_back(element);
}
