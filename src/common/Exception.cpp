#include "Exception.h"

const char *Exception::what() const noexcept {
    return message.c_str();
}

Exception::Exception(std::string what) : message(std::move(what)) {}
