#ifndef TOWERDEFENSE_RAY_H
#define TOWERDEFENSE_RAY_H


#include "Spell.h"
#include "../Scenario.h"

class Ray : public Spell {
public:
    Ray(Scenario &scenario, unsigned int cooldown, unsigned int min_dmg,
        unsigned int max_dmg);

    void applyEffect(const Vector &position) override;

    // lanza un meteorito al enemigo dañandolo a el y a todos los cercanos
    void applyEffect(Enemy &enemy) override;

    bool canBeThrownBy(const std::string &element) override;

    void update() override;

    bool isActive() const override;

    bool isPositional() const override;

    Communication::PositionalPower::Type getPositionalType() const override;

    Communication::TargetPower::Type getTargetType() const override;

private:
    unsigned int min_dmg;
    unsigned int max_dmg;
};


#endif //TOWERDEFENSE_RAY_H
