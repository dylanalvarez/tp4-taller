//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_ACTION_H
#define TOWERDEFENSE_ACTION_H


#include "../../model/TowerDefenseGame.h"

class Client;

class Action {
public:
    virtual ~Action() = default;

    virtual void apply(TowerDefenseGame& game) = 0;
    virtual void apply(std::vector<Client>& clients) {};
};


#endif //TOWERDEFENSE_ACTION_H
