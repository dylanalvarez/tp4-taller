//
// Created by facundo on 31/10/17.
//

#include "SendMessageAction.h"
#include "../Client.h"

SendMessageAction::SendMessageAction(std::string& msg,
                                     std::string& nickname) :
        msg(std::move(msg)), name(nickname){}

void SendMessageAction::apply(Context& context) {
    context.getSocket().sendChatMessage(std::move(msg), name);
}
