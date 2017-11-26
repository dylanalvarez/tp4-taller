#ifndef TOWERDEFENSE_AIRTOWER_H
#define TOWERDEFENSE_AIRTOWER_H


#include "Tower.h"

#define units_to_move_back 4

class AirTower : public Tower {
public:
    AirTower(int id, Vector p, YAML::Node &properties,
             Scenario &scneario);

    ~AirTower() override;

    void attack() override;

    void levelupRange() override;

    void levelupDamage() override;

    void levelupReachOfImpact() override;

    void levelupSlowdown() override;

    int getSlowDownLevel() const override;

    int getReachLevel() const override;

    Communication::Tower::Damage getDamage_() const override;

    Communication::Tower::Type getType() const override;

    AirTower(const AirTower &) = delete;

    AirTower &operator=(const AirTower &) = delete;

    AirTower &operator=(AirTower &&) = delete;

    AirTower(AirTower &&) noexcept;

private:
    unsigned int dmg_to_flying_units;
    unsigned int dmg_to_flying_units_upgrade;
};


#endif //TOWERDEFENSE_AIRTOWER_H
