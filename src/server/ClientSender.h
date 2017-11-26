#ifndef TOWERDEFENSE_CLIENTSENDER_H
#define TOWERDEFENSE_CLIENTSENDER_H


#include "../common/BlockingQueue.h"
#include "../common/Thread.h"

class ClientSender : public Thread {
public:
    ClientSender(GameServerSocket &socket, BlockingQueue &queue);

    ~ClientSender() override;

    void run() override;

    void stop();

    bool isOperational() const;

    ClientSender(const ClientSender &) = delete;

    ClientSender &operator=(const ClientSender &) = delete;

    ClientSender(ClientSender &&) = delete;

private:
    bool keep_running;
    BlockingQueue &queue;
    Context context;

};


#endif //TOWERDEFENSE_CLIENTSENDER_H
