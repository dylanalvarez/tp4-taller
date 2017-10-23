//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_TOWER_H
#define TOWERDEFENSE_TOWER_H


#include "../Vector.h"
#include "../Range.h"
#include "../Enemy.h"
#include "../Upgrades/RangeLevelup.h"
#include <string>

class Scenario;

class Tower {
public:
    Tower(int id, Vector position, const YAML::Node& properties,
          Scenario& scenario);
    virtual ~Tower();

    virtual void attack() = 0;
    virtual void levelupRange() = 0;
    virtual void levelupDamage() = 0;
    virtual void levelupReachOfImpact() = 0;
    virtual void levelupSlowdown() = 0;

    // realiza un levelup en el tipo especificado
    // rango, daño, alcance, o relentizado
    void levelup(const std::string& type);

    double getExperience() const;

    const Vector& getPosition() const;

    const Range& getRange() const;

    unsigned int getDamage() const;

    Tower(const Tower&) = delete;
    Tower& operator=(const Tower&) = delete;
    Tower& operator=(Tower&&) = delete;
    Tower(Tower&&);

protected:
    int id;
    double experience;
    Vector position;

    const YAML::Node& properties;
    Scenario& scenario;

    unsigned int dmg;
    Range range;

    unsigned int attack_cooldown;
    time_t last_attack_time;
    Enemy* current_target;
    unsigned int damage_dealed_to_current_target;

    int range_level;
    int dmg_level;

    std::map<std::string, LevelupType*> levelup_types;

    bool isCurrentTargetOutOfRange(const std::vector<Enemy*>&) const;
    void changeTarget(const std::vector<Enemy*>&);
    void hitCurrentTarget(unsigned int dmg);
};


#endif //TOWERDEFENSE_TOWER_H
