//
// Created by facundo on 23/10/17.
//

#ifndef TOWERDEFENSE_FIREWALL_H
#define TOWERDEFENSE_FIREWALL_H


#include "Spell.h"
#include "../Scenario.h"

class FireWall : public Spell {
public:
    explicit FireWall(Scenario& scenario, unsigned int cooldown,
                      unsigned int dmg, unsigned int duration);

    // crea un muro de fuego que daña a todos los enemigos en la posicion
    void applyEffect(const Vector& position) override;

    void applyEffect(Enemy& enemy) override;

    bool canBeThrownBy(const std::string& element) override;

    void update() override;

    bool isActive() const override;

    bool isPositional() const override;
    Communication::PositionalPower::Type getPositionalType() const override;
    Communication::TargetPower::Type getTargetType() const override;

private:
    unsigned int duration;
    unsigned int dmg;
};


#endif //TOWERDEFENSE_FIREWALL_H
