//
// Created by facundo on 31/10/17.
//

#include "SendMessageAction.h"
#include "../Client.h"

SendMessageAction::SendMessageAction(const std::string& msg,
                                     const std::string& nickname) :
        msg(msg), name(nickname) {}

void SendMessageAction::apply(Context& context) {
    context.getSocket().sendChatMessage(msg, name);
}
