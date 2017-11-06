//
// Created by facundo on 05/11/17.
//

#ifndef TOWERDEFENSE_PINGACTION_H
#define TOWERDEFENSE_PINGACTION_H


#include "../../model/Vector.h"
#include "Action.h"

class PingAction : public Action {
public:
    explicit PingAction(Vector location);

    void apply(Context& context) override;

private:
    Vector position;
};


#endif //TOWERDEFENSE_PINGACTION_H
