#ifndef TP4_TALLER_COMMUNICATION_UTILS_H
#define TP4_TALLER_COMMUNICATION_UTILS_H

#include <map>
#include <vector>
#include <string>

namespace Communication {
struct NameAndID {
    std::string name;
    int id;
};

struct Upgrade {
    enum Type {
        range, damage, reach, slowdown
    };
    Type type;
    int towerID;
};

enum Element {
    desert, volcano, ice, meadow
};

struct Enemy {
    enum Type {
        greenDemon, goatMan, undead, spectre, bloodyHawk, abmonible
    };
    int id, x, y;
    Type type;
};

struct Tower {
    struct EnemySlowdown {
        int percentage, duration;
    };
    struct Damage {
        int normal, flying, close_by;
    };
    enum Type {
        earth, water, fire, air
    };

    int id, level, experience, rangeInSquares, ExplosionRange, x, y;

    EnemySlowdown slowdown;
    Damage damage;
    Type type;
};

struct PositionalPower {
    enum Type {
        meteorite, terraforming, fissure, fireWall, blizzard, tornado
    };
    Type type;
    int x, y;
};

struct TargetPower {
    enum Type {
        freezing, ray
    };
    Type type;
    int enemyID;
};

struct GameState {
    enum State {
        won, lost, ongoing
    };
    std::vector<Enemy> enemy;
    std::vector<Tower> towers;
    std::vector<PositionalPower> positionalPowers;
    std::vector<TargetPower> targetPowers;
};
}


#endif //TP4_TALLER_COMMUNICATION_UTILS_H
