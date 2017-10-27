//
// Created by facundo on 27/10/17.
//

#include "Server.h"

Server::Server(const std::string& port) : accept_socket(port) {}

Server::~Server() {
    while (accept_socket.canAccept()) {

    }
}

void Server::run() {

}

void Server::stop() {

}
