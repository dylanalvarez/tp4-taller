//
// Created by facundo on 27/10/17.
//

#ifndef TOWERDEFENSE_SERVER_H
#define TOWERDEFENSE_SERVER_H


#include "Thread.h"
#include "../../client-server/server_ServerSocket.h"
#include "Match.h"

class Server : public Thread {
public:
    explicit Server(const std::string& port);
    ~Server() override;

    // cuando el server se inicia comienza a aceptar clientes
    // y los distribuye por las distintas partidas
    void run() override;

    void stop();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;

private:
    ServerSocket accept_socket;
    std::vector<Match> matchs;
};


#endif //TOWERDEFENSE_SERVER_H
