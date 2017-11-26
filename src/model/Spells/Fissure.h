#ifndef TOWERDEFENSE_FISSURE_H
#define TOWERDEFENSE_FISSURE_H


#include "Spell.h"
#include "../Scenario.h"

class Fissure : public Spell {
public:
    explicit Fissure(Scenario &scenario, unsigned int cooldown,
                     unsigned int duration);

    // abre una grieta en la posicion que mata a todos los enemigos
    // que caen en ella
    // Pre: la posicion debe ser un camino
    void applyEffect(const Vector &position) override;

    void applyEffect(Enemy &enemy) override;

    bool canBeThrownBy(const std::string &element) override;

    void update() override;

    bool isActive() const override;

    bool isPositional() const override;

    Communication::PositionalPower::Type getPositionalType() const override;

    Communication::TargetPower::Type getTargetType() const override;

private:
    unsigned int duration;
};


#endif //TOWERDEFENSE_FISSURE_H
