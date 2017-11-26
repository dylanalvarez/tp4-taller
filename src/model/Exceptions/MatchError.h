#ifndef TOWERDEFENSE_MATCHERROR_H
#define TOWERDEFENSE_MATCHERROR_H

#include <exception>
#include <string>

class MatchError : public std::exception {
public:
    explicit MatchError(const std::string &info) noexcept;

    ~MatchError() override;

    const char *what() const noexcept override;

    MatchError(const MatchError &) noexcept;

    MatchError &operator=(const MatchError &) noexcept;

private:
    std::string info;
};


#endif //TOWERDEFENSE_MATCHERROR_H
