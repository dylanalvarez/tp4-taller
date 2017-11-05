//
// Created by facundo on 03/11/17.
//

#ifndef TOWERDEFENSE_DISTRIBUTEMESSAGEACTION_H
#define TOWERDEFENSE_DISTRIBUTEMESSAGEACTION_H


#include "Action.h"

class DistributeMessageAction : public Action {
public:
    explicit DistributeMessageAction(std::string&& msg);

    void apply(Context& contex) override;

private:
    std::string msg;
};


#endif //TOWERDEFENSE_DISTRIBUTEMESSAGEACTION_H
