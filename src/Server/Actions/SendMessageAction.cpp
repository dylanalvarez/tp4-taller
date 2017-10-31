//
// Created by facundo on 31/10/17.
//

#include "SendMessageAction.h"
#include "../Client.h"

SendMessageAction::SendMessageAction(std::string &msg) : msg(msg) {}

void SendMessageAction::apply(std::vector<Client> &clients) {
    for (Client& client : clients) {
        client.sendMessage(msg);
    }
}
