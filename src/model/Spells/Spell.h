//
// Created by facundo on 23/10/17.
//

#ifndef TOWERDEFENSE_SPELL_H
#define TOWERDEFENSE_SPELL_H


#include "../Vector.h"
#include "../Enemy.h"

class Spell {
public:
    virtual void applyEffect(const Vector& position) = 0;

    virtual bool canBeThrownBy(const std::string& element) = 0;

    virtual void attack() = 0;

protected:
    bool is_active = false;
};


#endif //TOWERDEFENSE_SPELL_H
