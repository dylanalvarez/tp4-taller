//
// Created by facundo on 23/10/17.
//

#ifndef TOWERDEFENSE_BLIZZARD_H
#define TOWERDEFENSE_BLIZZARD_H


#include "Spell.h"
#include "../Scenario.h"

class Blizzard : public Spell {
public:
    explicit Blizzard(Scenario& scenario, unsigned int cooldown,
                      unsigned int duration, unsigned int dmg,
                      unsigned int speed_reduction,
                      unsigned int speed_reduction_duration);

    // crea una tormenta helada que daña y relentiza a los enemigos
    // que pasen por la posicion
    void applyEffect(const Vector& position) override;

    void applyEffect(Enemy& enemy) override;

    bool canBeThrownBy(const std::string& element) override;

    void attack() override;

    bool isActive() const override;

private:
    unsigned int dmg;
    unsigned int duration;
    unsigned int speed_reduction;
    unsigned int speed_reduction_duration;
};


#endif //TOWERDEFENSE_BLIZZARD_H
