#ifndef TOWERDEFENSE_INVALIDSIZEEXCEPTION_H
#define TOWERDEFENSE_INVALIDSIZEEXCEPTION_H


#include "../common/Exception.h"

class InvalidSizeException : public std::exception {
public:
    explicit InvalidSizeException(std::string what)
            : message(std::move(what)) {}

    const char *what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

#endif //TOWERDEFENSE_INVALIDSIZEEXCEPTION_H
