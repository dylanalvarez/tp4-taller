//
// Created by facundo on 03/11/17.
//

#include "ClientSender.h"
#include "../common/Exception.h"

ClientSender::ClientSender(GameServerSocket &socket, BlockingQueue &queue) :
        queue(queue), context(socket) {
    keep_running = true;
}

ClientSender::~ClientSender() {
    while (!queue.empty()) {
        queue.pop();
    }
}

void ClientSender::run() {
    while (keep_running) {
        try {
            queue.front().apply(context);
            queue.pop();
        } catch (Exception& e) {
            keep_running = false;
        }
    }
}

void ClientSender::stop() {
    keep_running = false;
}

bool ClientSender::isOperational() const {
    return keep_running;
}
