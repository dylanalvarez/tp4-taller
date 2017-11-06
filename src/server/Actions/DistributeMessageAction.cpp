//
// Created by facundo on 03/11/17.
//

#include "DistributeMessageAction.h"
#include "../Client.h"

DistributeMessageAction::DistributeMessageAction(std::string &&msg,
                                                 std::string&& nickname) :
        msg(std::move(msg)), nickname(std::move(nickname)) {}

void DistributeMessageAction::apply(Context &contex) {
    for (Client* client : contex.getClients()) {
        client->sendMessage(std::move(msg), std::move(nickname));
    }
}
