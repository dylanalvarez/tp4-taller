//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_SENDMESSAGEACTION_H
#define TOWERDEFENSE_SENDMESSAGEACTION_H


#include "Action.h"

class SendMessageAction : public Action {
public:
    explicit SendMessageAction(std::string& msg);

    void apply(std::vector<Client>& clients) override;

    SendMessageAction(const SendMessageAction&) = delete;
    SendMessageAction& operator=(const SendMessageAction&) = delete;

private:
    std::string msg;
};


#endif //TOWERDEFENSE_SENDMESSAGEACTION_H
