//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_ACTION_H
#define TOWERDEFENSE_ACTION_H

#include "../../model/TowerDefenseGame.h"
#include "../Context.h"

class Client;
class Context;

class Action {
public:
    virtual ~Action() = default;

    virtual void apply(Context&) = 0;
};


#endif //TOWERDEFENSE_ACTION_H
