//
// Created by facundo on 03/11/17.
//

#include "DistributeMessageAction.h"
#include "../Client.h"

DistributeMessageAction::DistributeMessageAction(std::string &&msg) :
        msg(std::move(msg)) {}

void DistributeMessageAction::apply(Context &contex) {
    /*for (Client& client : contex.getClients()) {
        client.sendMessage(msg);
    }*/
}
