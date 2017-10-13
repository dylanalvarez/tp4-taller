//
// Created by facundo on 10/10/17.
//

#ifndef TOWERDEFENSE_POSITION_H
#define TOWERDEFENSE_POSITION_H


class Position {
public:
    Position(float x, float y);

    float getX() const;
    float getY() const;

    Position& operator+=(float);
    Position& operator+=(const Position&);

private:
    float x;
    float y;
};


#endif //TOWERDEFENSE_POSITION_H
