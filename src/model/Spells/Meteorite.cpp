#include "Meteorite.h"
#include "../Exceptions/MatchError.h"

Meteorite::Meteorite(Scenario &scenario, unsigned int cooldown,
                     unsigned int reach, unsigned int dmg,
                     unsigned int dmg_to_nearby_enemies) :
        Spell(scenario, cooldown),
        reach(reach),
        dmg(dmg),
        dmg_to_nearby_enemies(dmg_to_nearby_enemies) {}

void Meteorite::applyEffect(Enemy &enemy) {
    if (isOnCooldown()) { return; }

    enemy.reduceLife(dmg);

    std::vector<Enemy *> enemies = scenario.getEnemiesInRange(
            Range(enemy.getCurrentPosition()), reach * tile_size);

    target_id = enemy.getID();

    for (Enemy *target : enemies) {
        if (target->getID() == enemy.getID()) { continue; }
        target->reduceLife(dmg_to_nearby_enemies);
    }

    is_active = true;
    last_activation_time = time(nullptr);
}

bool Meteorite::canBeThrownBy(const std::string &element) {
    return element == "fire";
}

void Meteorite::update() { is_active = false; }

void Meteorite::applyEffect(const Vector &position) {}

bool Meteorite::isActive() const {
    return is_active;
}

Communication::PositionalPower::Type Meteorite::getPositionalType() const {
    throw MatchError("Error al solicitar tipo de hechizo:"
                             " meteorite no es posicional");
}

Communication::TargetPower::Type Meteorite::getTargetType() const {
    return Communication::TargetPower::Type::meteorite;
}

bool Meteorite::isPositional() const {
    return false;
}
