//
// Created by facundo on 16/10/17.
//

#include "EnemyError.h"

EnemyError::EnemyError(const std::string& info) noexcept : info(info) {}

EnemyError::~EnemyError() = default;

const char *EnemyError::what() const noexcept {
    return info.c_str();
}

EnemyError::EnemyError(const EnemyError& other) noexcept {
    this->info = other.info;
}

EnemyError &EnemyError::operator=(const EnemyError& other) noexcept {
    this->info = other.info;
    return *this;
}
