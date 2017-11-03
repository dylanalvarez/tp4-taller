//
// Created by facundo on 03/11/17.
//

#ifndef TOWERDEFENSE_SENDGAMESTATEACTION_H
#define TOWERDEFENSE_SENDGAMESTATEACTION_H


#include "Action.h"

class SendGameStateAction : public Action {
public:
    explicit SendGameStateAction(const Communication::GameState&);

    void apply(Context&) override;

private:
    const Communication::GameState& gameState;
};


#endif //TOWERDEFENSE_SENDGAMESTATEACTION_H
