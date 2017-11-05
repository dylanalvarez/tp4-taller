//
// Created by facundo on 03/11/17.
//

#include "ClientSender.h"

ClientSender::ClientSender(GameServerSocket &socket, BlockingQueue &queue) :
        queue(queue), context(socket) {
    keep_running = true;
}

ClientSender::~ClientSender() = default;

void ClientSender::run() {
    while (keep_running) {
        try {
            queue.front().apply(context);
            queue.pop();
        } catch (std::exception& e) {
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
