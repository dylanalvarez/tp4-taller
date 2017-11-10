//
// Created by facundo on 23/10/17.
//

#ifndef TOWERDEFENSE_SPELL_H
#define TOWERDEFENSE_SPELL_H


#include "../Vector.h"
#include "../Enemy.h"
#include "../Scenario.h"

class Spell {
public:
    Spell(Scenario& scenario, unsigned int cooldown);

    virtual ~Spell();
    // aplica el efecto del hechizo al enemigo o la posicion
    virtual void applyEffect(const Vector& position) = 0;
    virtual void applyEffect(Enemy& enemy) = 0;

    // retorna si puede ser lanzado por un tipo de elemento
    // por ejemplo tornato puede ser lanzado por el elemento air
    virtual bool canBeThrownBy(const std::string& element) = 0;

    // realiza el ataque del hechizo si se activo con activate
    // o lo desactiva si es un hechizo instantaneo
    virtual void update() = 0;

    virtual bool isActive() const = 0;

    // activa el hechizo
    void activate(const Vector& position);

    // chequea si paso su duracion
    void checkIfIsActive(unsigned int duration);

    // chequea si paso su cooldown
    bool isOnCooldown();

    virtual bool isPositional() const = 0;
    virtual Communication::PositionalPower::Type getPositionalType() const = 0;
    virtual Communication::TargetPower::Type getTargetType() const = 0;

    const Vector& getPosition() const;
    const int getTargetID() const;

protected:
    Vector position;
    int target_id;
    bool is_active = false;
    time_t last_activation_time;
    Scenario& scenario;
    unsigned int cooldown;
    bool is_on_cooldown;

    const int tile_size = 44; // en pixeles
};

#endif //TOWERDEFENSE_SPELL_H
