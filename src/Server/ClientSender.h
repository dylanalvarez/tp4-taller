//
// Created by facundo on 03/11/17.
//

#ifndef TOWERDEFENSE_CLIENTSENDER_H
#define TOWERDEFENSE_CLIENTSENDER_H


#include "../../estandar_de_comunicacion/GameServerSocket.h"
#include "BlockingQueue.h"

class ClientSender : public Thread {
public:
    ClientSender(GameServerSocket& socket, BlockingQueue& queue);

    ~ClientSender() override;

    void run() override;

    void stop();

    ClientSender(const ClientSender&) = delete;
    ClientSender& operator=(const ClientSender&) = delete;
    ClientSender(ClientSender&&) noexcept ;

private:
    bool keep_running;
    GameServerSocket& socket;
    BlockingQueue& queue;
    Context context;

};


#endif //TOWERDEFENSE_CLIENTSENDER_H
