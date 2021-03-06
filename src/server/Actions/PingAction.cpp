#include "PingAction.h"
#include "../../common/GameServerSocket.h"

PingAction::PingAction(Vector location) : position(location) {}

void PingAction::apply(Context &context) {
    context.getSocket().sendPing((int) position.getX(), (int) position.getY());
}
