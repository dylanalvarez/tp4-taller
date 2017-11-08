//
// Created by facundo on 17/10/17.
//

#ifndef TOWERDEFENSE_PLAYER_H
#define TOWERDEFENSE_PLAYER_H

#include <string>
#include <vector>
#include "Towers/Tower.h"

class Player {
public:
    Player(std::string name, std::string element);
    Player(std::string name);

    void addTower(const Tower& tower);
    void addElement(const std::string& element);

    const std::string& getName() const;
    const std::vector<std::string>& getElements() const;
    const std::vector<const Tower*> getTowers() const;
    bool containsTower(const Tower& tower) const;
    bool canBuildTower(const std::string& type) const;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) noexcept ;
    Player& operator=(Player&&) noexcept ;

private:
    std::vector<std::string> elements;
    std::string name;
    std::vector<const Tower*> towers;
};


#endif //TOWERDEFENSE_PLAYER_H
