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

    void attack() override;

private:
    Vector position;
    unsigned int cooldown;
    unsigned int duration;
    unsigned int dmg;
    time_t last_activation_time;
    Scenario& scenario;
};


#endif //TOWERDEFENSE_FIREWALL_H
