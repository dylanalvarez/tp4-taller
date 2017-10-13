//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_TOWER_H
#define TOWERDEFENSE_TOWER_H


class Tower {
public:
    Tower();
    virtual ~Tower();

    virtual void attack() = 0;

    unsigned int getExperience() const;

protected:
    unsigned int experience;
};


#endif //TOWERDEFENSE_TOWER_H
