#include "SendMessageAction.h"
#include "../Client.h"

SendMessageAction::SendMessageAction(const std::string &msg,
                                     const std::string &nickname) :
        msg(msg), name(nickname) {}

void SendMessageAction::apply(Context &context) {
    context.getSocket().sendChatMessage(msg, name);
}
