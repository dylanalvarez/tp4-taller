#ifndef TP4_TALLER_EXCEPTION_H
#define TP4_TALLER_EXCEPTION_H


#include <exception>
#include <string>

class Exception : public std::exception {
public:
    explicit Exception(std::string what);

    const char *what() const noexcept override;

private:
    std::string message;
};


#endif //TP4_TALLER_EXCEPTION_H
