//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_TOWER_H
#define TOWERDEFENSE_TOWER_H


#include "../Vector.h"
#include "../Range.h"
#include "../Enemy.h"

class Scenario;

class Tower {
public:
    Tower(int id, Vector position, const YAML::Node& properties,
          Scenario& scenario);
    virtual ~Tower();

    virtual void attack() = 0;

    unsigned int getExperience() const;

    const Vector& getPosition() const;

    Tower(const Tower&) = delete;
    Tower& operator=(const Tower&) = delete;
    Tower& operator=(Tower&&) = delete;
    Tower(Tower&&) noexcept ;

protected:
    int id;
    unsigned int experience;
    Vector position;
    const YAML::Node& properties;
    Scenario& scenario;

    Range range;
    unsigned int dmg;
    unsigned int attack_cooldown;
    time_t last_attack_time;
    Enemy* current_target;
};


#endif //TOWERDEFENSE_TOWER_H
