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

    static std::string to_string(const Enemy::Type& type) {
        std::vector<std::string> states {"greenDemon", "goatMan", "undead", "spectre", "bloodyHawk", "abmonible"};
        return states[type];
    }

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

    static std::string to_string(const Tower::Type& type) {
        std::vector<std::string> states {"earth", "water", "fire", "air"};
        return states[type];
    }

    int id, level, experience, rangeInSquares, ExplosionRange, x, y;

    EnemySlowdown slowdown;
    Damage damage;
    Type type;
};

struct PositionalPower {
    enum Type {
        meteorite, terraforming, fissure, fireWall, blizzard, tornado
    };

    static std::string to_string(const PositionalPower::Type& type) {
        std::vector<std::string> states {"meteorite", "terraforming", "fissure", "fireWall", "blizzard", "tornado"};
        return states[type];
    }

    Type type;
    int x, y;
};

struct TargetPower {
    enum Type {
        freezing, ray
    };

    static std::string to_string(const TargetPower::Type& type) {
        std::vector<std::string> states {"freezing", "ray"};
        return states[type];
    }

    Type type;
    int enemyID;
};

struct GameState {
    enum State {
        won, lost, ongoing
    };

    static std::string to_string(const GameState::State& state) {
        std::vector<std::string> states {"won", "lost", "ongoing"};
        return states[state];
    }

    State state;
    std::vector<Enemy> enemy;
    std::vector<Tower> towers;
    std::vector<PositionalPower> positionalPowers;
    std::vector<TargetPower> targetPowers;
};
}


#endif //TP4_TALLER_COMMUNICATION_UTILS_H
