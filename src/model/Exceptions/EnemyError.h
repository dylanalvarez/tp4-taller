#ifndef TOWERDEFENSE_ENEMYERROR_H
#define TOWERDEFENSE_ENEMYERROR_H


#include <exception>
#include <string>

class EnemyError : public std::exception {
public:
    explicit EnemyError(const std::string &info) noexcept;

    ~EnemyError() override;

    const char *what() const noexcept override;

    EnemyError(const EnemyError &) noexcept;

    EnemyError &operator=(const EnemyError &) noexcept;

private:
    std::string info;
};


#endif //TOWERDEFENSE_ENEMYERROR_H
