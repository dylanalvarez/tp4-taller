//
// Created by facundo on 03/11/17.
//

#include "ClientSender.h"

ClientSender::ClientSender(GameServerSocket &socket, BlockingQueue &queue) :
        socket(socket), queue(queue), context(socket) {
    keep_running = true;
}

ClientSender::~ClientSender() = default;

void ClientSender::run() {
    while (keep_running) {
        queue.front().apply(context);
        queue.pop();
    }
}

void ClientSender::stop() {
    keep_running = false;
}
