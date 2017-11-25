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
        NameAndID(const std::string &, int);

        NameAndID();

        std::string name;
        int id;
    };

    struct Upgrade {
        Upgrade() = default;
        Upgrade(const std::string& type, int tower_id);

        enum Type {
            range, damage, reach, slowdown
        };

        static std::string to_string(const Type &type);

        Type type;
        int towerID;
    };

    enum Element {
        earth, water, fire, air
    };

    std::string to_string(const Element &element);
    Element to_element(const std::string& element);

    struct Enemy {
        enum Type {
            greenDemon, goatMan, undead, spectre, bloodyHawk, abmonible
        };

        static std::string to_string(const Enemy::Type &type);

        Enemy(const std::string &type, int id, int x, int y);

        Enemy(Type type, int id, int x, int y);

        int id, x, y;
        Type type;
    };

    struct Tower {
        struct EnemySlowdown {
            EnemySlowdown(int percentage, int duration);

            int percentage, duration;
        };

        struct Damage {
            Damage(int normal, int flying, int close_by);

            int normal, flying, close_by;
        };

        enum Type {
            earth, water, fire, air
        };

        struct Level {
            Level(int range, int damage, int reach, int slowdown);

            int range, damage, reach, slowdown;
        };

        static std::string to_string(const Tower::Type &type);
        static Tower::Type string_to_type(const std::string& type);

        Tower(int id, Level level, int experience, int rangeInSquares,
              int ExplosionRange, int x, int y, EnemySlowdown slowdown,
              Damage damage, const std::string &type, bool is_attacking = false,
              int current_target_id = 0);

        Tower(int id, Level level, int experience, int rangeInSquares,
              int ExplosionRange, int x, int y, EnemySlowdown slowdown,
              Damage damage, Type type, bool is_attacking = false,
              int current_target_id = 0);

        int id, experience, rangeInSquares, ExplosionRange, x, y;

        Level level;
        EnemySlowdown slowdown;
        Damage damage;
        Type type;
        bool is_attacking;
        int current_target_id;
    };

    struct PositionalPower {
        enum Type {
            terraforming, fissure, fireWall, blizzard, tornado
        };

        static std::string to_string(const PositionalPower::Type &type);

        PositionalPower(const std::string &, int x, int y);

        PositionalPower(Type, int x, int y);

        Type type;
        int x, y;
    };

    struct TargetPower {
        enum Type {
            freezing, ray, meteorite
        };

        static std::string to_string(const TargetPower::Type &type);

        TargetPower(const std::string &type, int enemyID);

        TargetPower(Type type, int enemyID);

        Type type;
        int enemyID;
    };

    struct GameState {
        enum State {
            won, lost, ongoing
        };

        static std::string to_string(const GameState::State &state);

        void setState(const std::string &stateAsString);

        State state;
        std::vector<Enemy> enemies;
        std::vector<Tower> towers;
        std::vector<PositionalPower> positionalPowers;
        std::vector<TargetPower> targetPowers;
    };

    std::string toFixedLengthString(long messageLength, int length);
}


#endif //TP4_TALLER_COMMUNICATION_UTILS_H
