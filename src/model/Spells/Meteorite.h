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

    // abre una grieta en la posicion que mata a todos los enemigos
    // que caen en ella
    // Pre: la posicion debe ser un camino
    void applyEffect(const Vector& position) override;

    void applyEffect(Enemy& enemy) override;

    bool canBeThrownBy(const std::string& element) override;

    void attack() override;

private:
    unsigned int cooldown;
    unsigned int reach;
    unsigned int dmg;
    unsigned int dmg_to_nearby_enemies;
    time_t last_activation_time;
    Scenario& scenario;
};


#endif //TOWERDEFENSE_METEORITE_H
