#ifndef TOWERDEFENSE_TOWERERROR_H
#define TOWERDEFENSE_TOWERERROR_H


#include <exception>
#include <string>

class TowerError : public std::exception {
public:
    explicit TowerError(const std::string &info);

    const char *what() const noexcept override;

    TowerError(const TowerError &) noexcept;

    TowerError &operator=(const TowerError &) noexcept;

private:
    std::string info;
};


#endif //TOWERDEFENSE_TOWERERROR_H
