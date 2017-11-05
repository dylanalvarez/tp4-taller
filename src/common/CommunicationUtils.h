#ifndef TP4_TALLER_COMMUNICATION_UTILS_H
#define TP4_TALLER_COMMUNICATION_UTILS_H

#include <map>
#include <utility>
#include <vector>
#include <string>

#define OPCODE_CHARACTER_COUNT 2
#define MESSAGE_LENGTH_CHARACTER_COUNT 8

namespace Communication {
    struct NameAndID {
        NameAndID(std::string, int);
        NameAndID();

        std::string name;
        int id;
    };

    struct Upgrade {
        enum Type {
            range, damage, reach, slowdown
        };

        static std::string to_string(const Type &type);

        Type type;
        int towerID;
    };

    enum Element {
        desert, volcano, ice, meadow
    };

    std::string to_string(const Element &element);

    struct Enemy {
        enum Type {
            greenDemon, goatMan, undead, spectre, bloodyHawk, abmonible
        };

        static std::string to_string(const Enemy::Type &type);

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

        static std::string to_string(const Tower::Type &type);

        int id, level, experience, rangeInSquares, ExplosionRange, x, y;

        EnemySlowdown slowdown;
        Damage damage;
        Type type;
    };

    struct PositionalPower {
        enum Type {
            meteorite, terraforming, fissure, fireWall, blizzard, tornado
        };

        static std::string to_string(const PositionalPower::Type &type);

        Type type;
        int x, y;
    };

    struct TargetPower {
        enum Type {
            freezing, ray
        };

        static std::string to_string(const TargetPower::Type &type);

        Type type;
        int enemyID;
    };

    struct GameState {
        enum State {
            won, lost, ongoing
        };

        static std::string to_string(const GameState::State &state);

        State state;
        std::vector<Enemy> enemy;
        std::vector<Tower> towers;
        std::vector<PositionalPower> positionalPowers;
        std::vector<TargetPower> targetPowers;
    };

    std::string toFixedLengthString(long messageLength, int length);
}


#endif //TP4_TALLER_COMMUNICATION_UTILS_H
