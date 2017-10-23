//
// Created by facundo on 17/10/17.
//

#ifndef TOWERDEFENSE_PLAYER_H
#define TOWERDEFENSE_PLAYER_H

#include <string>
#include <vector>

class Player {
public:
    Player(const std::string& name, const std::string& element);

    const std::string& getName() const;
    const std::vector<std::string>& getElements() const;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) noexcept ;
    Player& operator=(Player&&) noexcept ;

private:
    std::vector<std::string> elements;
    std::string name;
};


#endif //TOWERDEFENSE_PLAYER_H
