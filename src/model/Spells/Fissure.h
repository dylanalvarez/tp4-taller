//
// Created by facundo on 23/10/17.
//

#ifndef TOWERDEFENSE_FISSURE_H
#define TOWERDEFENSE_FISSURE_H


#include "Spell.h"
#include "../Scenario.h"

class Fissure : public Spell {
public:
    explicit Fissure(Scenario& scenario, unsigned int cooldown,
                     unsigned int duration);

    // abre una grieta en la posicion que mata a todos los enemigos
    // que caen en ella
    // Pre: la posicion debe ser un camino
    void applyEffect(const Vector& position) override;

    void applyEffect(Enemy& enemy) override;

    bool canBeThrownBy(const std::string& element) override;

    void attack() override;

    bool isActive() const override;

private:
    unsigned int duration;
};


#endif //TOWERDEFENSE_FISSURE_H