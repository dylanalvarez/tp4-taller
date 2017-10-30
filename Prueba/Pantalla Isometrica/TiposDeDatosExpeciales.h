#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__


#define NoColicion 0


enum Elementos{
  fuego,agua,aire,tierra  };

enum Hechizo{
  Terraforming, Congelacion, Grieta, Ventisca, Meteorito, Tornado,
  MuroDeFuego, Rayos};

//este es la unica razon por la que esta esta libreraria
struct DatosPantalla{
//corregir idioma
  int width;
  int height;
  int desplasamientoX;
  int desplasamientoY;
};

struct Posicion{
  int X;
  int Y;
};


//estos estan aca temporalmente.
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
    State state;
    std::vector<Enemy> enemy;
    std::vector<Tower> towers;
    std::vector<PositionalPower> positionalPowers;
    std::vector<TargetPower> targetPowers;
};
}


#endif
