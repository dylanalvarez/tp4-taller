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

#define TILE_SIZE 88

class Scenario;

class Tower {
public:
    Tower(int id, Vector position, Scenario& scenario);

    virtual ~Tower();

    virtual void attack() = 0;

    // upgrades
    virtual void levelupRange() = 0;
    virtual void levelupDamage() = 0;
    virtual void levelupReachOfImpact() = 0;
    virtual void levelupSlowdown() = 0;
    
    bool operator==(const Tower& other);

    // realiza un levelup en el tipo especificado
    // rango, daño, alcance, o relentizado
    void levelup(const std::string& type);

    // getters
    double getExperience() const;
    const Vector& getPosition() const;
    const Range& getRange() const;
    unsigned int getDamage() const;

    bool isAttacking() const;

    int getRangeLevel() const;
    int getDamageLevel() const;
    int getCurrentTargetID() const;

    virtual int getSlowDownLevel() const = 0;
    virtual int getReachLevel() const = 0;

    int getID() const;

    virtual Communication::Tower::Damage getDamage_() const = 0;
    virtual Communication::Tower::Type getType() const = 0;
    virtual Communication::Tower::EnemySlowdown getslowdown() const;
    virtual int getExplosionRange() const;

    Tower(const Tower&) = delete;
    Tower& operator=(const Tower&) = delete;
    Tower& operator=(Tower&&) = delete;
    Tower(Tower&&) noexcept ;

protected:
    // info de torre
    int id;
    double experience;
    Vector position;
    bool is_attacking;

    // archivo de configuracion
    Scenario& scenario;

    // atributos
    unsigned int dmg;
    unsigned int dmg_upgrade;
    Range range;
    unsigned int range_upgrade;
    unsigned int attack_cooldown;
    time_t last_attack_time;
    Enemy* current_target;
    unsigned int damage_dealed_to_current_target;

    // atributos para calcular experiencia necesaria para levelear
    std::pair<int, float> range_levelingup_function_values;
    std::pair<int, float> dmg_levelingup_function_values;

    // levels
    int range_level;
    int dmg_level;

    std::map<std::string, LevelupType*> levelup_types;

    bool isCurrentTargetOutOfRange(const std::vector<Enemy*>&) const;
    void changeTarget(const std::vector<Enemy*>&);
    void hitCurrentTarget(unsigned int dmg);
    int getRangeInTileSizes(float range);
};

#endif //TOWERDEFENSE_TOWER_H
