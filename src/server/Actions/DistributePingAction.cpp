//
// Created by facundo on 05/11/17.
//

#include "DistributePingAction.h"
#include "../Client.h"

DistributePingAction::DistributePingAction(Vector location) : location(location) {}

void DistributePingAction::apply(Context &context) {
    for (Client* client : context.getClients()) {
        client->sendPing(location);
    }
}
