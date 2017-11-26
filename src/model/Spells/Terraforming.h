//
// Created by facundo on 23/10/17.
//

#ifndef TOWERDEFENSE_TERRAFORMING_H
#define TOWERDEFENSE_TERRAFORMING_H


#include "Spell.h"
#include "../Scenario.h"

class Terraforming : public Spell {
public:
    explicit Terraforming(Scenario &scenario, unsigned int cooldown);

    // crea terreno firme en la posicion especificada en el constructor
    // Pre: debe ser una posicion valida (no debe ser camino ni terreno firme)
    void applyEffect(const Vector &position) override;

    void applyEffect(Enemy &enemy) override;

    bool canBeThrownBy(const std::string &element) override;

    void update() override;

    bool isActive() const override;

    bool isPositional() const override;

    Communication::PositionalPower::Type getPositionalType() const override;

    Communication::TargetPower::Type getTargetType() const override;
};


#endif //TOWERDEFENSE_TERRAFORMING_H
