//
// Created by facundo on 23/10/17.
//

#ifndef TOWERDEFENSE_TERRAFORMING_H
#define TOWERDEFENSE_TERRAFORMING_H


#include "Spell.h"
#include "../Scenario.h"

class Terraforming : public Spell {
public:
    explicit Terraforming(Scenario& scenario, unsigned int cooldown);

    // crea terreno firme en la posicion especificada en el constructor
    // Pre: debe ser una posicion valida (no debe ser camino ni terreno firme)
    void applyEffect(const Vector& position) override;

    void applyEffect(Enemy& enemy) override;

    bool canBeThrownBy(const std::string& element) override;

    void attack() override;

private:
    unsigned int cooldown;
    time_t last_activation_time;
    Scenario& scenario;
};


#endif //TOWERDEFENSE_TERRAFORMING_H
