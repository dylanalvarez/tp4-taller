//
// Created by facundo on 17/10/17.
//

#ifndef TOWERDEFENSE_PLAYER_H
#define TOWERDEFENSE_PLAYER_H

#include <string>

class Player {
public:
    explicit Player(const std::string& name);

    const std::string& getName() const;

private:
    const std::string name;
};


#endif //TOWERDEFENSE_PLAYER_H
