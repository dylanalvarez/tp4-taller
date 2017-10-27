//
// Created by facundo on 23/10/17.
//

#ifndef TOWERDEFENSE_FREEZING_H
#define TOWERDEFENSE_FREEZING_H


#include "Spell.h"
#include "../Scenario.h"

class Freezing : public Spell {
public:
    explicit Freezing(Scenario& scenario, unsigned int cooldown, unsigned int duration);

    void applyEffect(const Vector& position) override;

    // congela un enemigo, reduciendo su velocidad de movimiento en un %100
    void applyEffect(Enemy& enemy) override;

    bool canBeThrownBy(const std::string& element) override;

    void attack() override;

    bool isActive() const override;

    bool isPositional() const override;
    Communication::PositionalPower::Type getPositionalType() const override;
    Communication::TargetPower::Type getTargetType() const override;

private:
    unsigned int duration;
};


#endif //TOWERDEFENSE_FREEZING_H
