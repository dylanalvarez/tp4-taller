//
// Created by facundo on 22/10/17.
//

#ifndef TOWERDEFENSE_LEVELUPTYPE_H
#define TOWERDEFENSE_LEVELUPTYPE_H

class Tower;

class LevelupType {
public:
    explicit LevelupType(Tower &tower);

    virtual ~LevelupType();

    virtual void levelup() = 0;

protected:
    Tower &tower;
};


#endif //TOWERDEFENSE_LEVELUPTYPE_H
