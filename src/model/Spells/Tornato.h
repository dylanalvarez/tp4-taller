//
// Created by facundo on 24/10/17.
//

#ifndef TOWERDEFENSE_TORNATO_H
#define TOWERDEFENSE_TORNATO_H


#include "Spell.h"
#include "FireWall.h"

class Tornato : public Spell {
public:
    explicit Tornato(Scenario& scenario, unsigned int cooldown,
                     unsigned int min_dmg, unsigned int max_dmg, unsigned int duration);

    // crea un tornado que daña a todos los enemigos con un
    // daño aleatorio entre min_dmg y max_dmg
    void applyEffect(const Vector& position) override;

    void applyEffect(Enemy& enemy) override;

    bool canBeThrownBy(const std::string& element) override;

    void attack() override;

    bool isActive() const override;

private:
    Vector position;
    unsigned int cooldown;
    unsigned int duration;
    unsigned int min_dmg;
    unsigned int max_dmg;
    time_t last_activation_time;
    Scenario& scenario;
};


#endif //TOWERDEFENSE_TORNATO_H
