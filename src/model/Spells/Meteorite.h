//
// Created by facundo on 23/10/17.
//

#ifndef TOWERDEFENSE_METEORITE_H
#define TOWERDEFENSE_METEORITE_H


#include "Spell.h"
#include "../Scenario.h"

class Meteorite : public Spell {
public:
    explicit Meteorite(Scenario& scenario, unsigned int cooldown,
                       unsigned int reach, unsigned int dmg,
                       unsigned int dmg_to_nearby_enemies);

    void applyEffect(const Vector& position) override;

    // lanza un meteorito al enemigo dañandolo a el y a todos los cercanos
    void applyEffect(Enemy& enemy) override;

    bool canBeThrownBy(const std::string& element) override;

    void update() override;

    bool isActive() const override;

    bool isPositional() const override;
    Communication::PositionalPower::Type getPositionalType() const override;
    Communication::TargetPower::Type getTargetType() const override;

private:
    unsigned int reach;
    unsigned int dmg;
    unsigned int dmg_to_nearby_enemies;
};


#endif //TOWERDEFENSE_METEORITE_H
