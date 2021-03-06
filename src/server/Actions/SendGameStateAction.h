#ifndef TOWERDEFENSE_SENDGAMESTATEACTION_H
#define TOWERDEFENSE_SENDGAMESTATEACTION_H


#include "../../common/GameServerSocket.h"
#include "Action.h"

class SendGameStateAction : public Action {
public:
    explicit SendGameStateAction(const Communication::GameState &);

    void apply(Context &) override;

private:
    const Communication::GameState &gameState;
};


#endif //TOWERDEFENSE_SENDGAMESTATEACTION_H
