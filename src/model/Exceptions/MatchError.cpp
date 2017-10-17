//
// Created by facundo on 17/10/17.
//

#include "MatchError.h"

MatchError::MatchError(const std::string& info) noexcept : info(info) {}

MatchError::~MatchError() = default;

MatchError &MatchError::operator=(const MatchError& other) noexcept {
    this->info = other.info;
    return *this;
}

const char *MatchError::what() const noexcept {
    return info.c_str();
}

MatchError::MatchError(const MatchError& other) noexcept {
    this->info = other.info;
}
