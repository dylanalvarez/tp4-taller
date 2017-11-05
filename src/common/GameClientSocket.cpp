#include "Socket.h"
#include "GameClientSocket.h"

GameClientSocket::GameClientSocket(GameClientReceiver &receiver,
                                   Socket &&socket)
        : receiver(receiver), socket(std::move(socket)) {}