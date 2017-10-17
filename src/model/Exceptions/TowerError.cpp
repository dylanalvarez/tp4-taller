//
// Created by facundo on 17/10/17.
//

#include "TowerError.h"

TowerError::TowerError(const std::string &info) : info(info) {}

const char *TowerError::what() const noexcept {
    return info.c_str();
}

TowerError::TowerError(const TowerError& other) noexcept {
    this->info = other.info;
}

TowerError &TowerError::operator=(const TowerError& other) noexcept {
    this->info = other.info;
    return *this;
}
