#ifndef TP4_TALLER_GAME_SERVER_SOCKET_H
#define TP4_TALLER_GAME_SERVER_SOCKET_H

#include <string>
#include "CommunicationUtils.h"
#include "GameServerReceiver.h"

class GameServerSocket {
public:
    // When it recieves a message, it will invoke a method in the receiver.
    GameServerSocket(const GameServerReceiver &receiver, int port);

    void sendInitialData(const std::vector<NameAndID> &matches,
                         const std::vector<NameAndID> &maps);

    // Filename relative to executable
    void sendMap(std::string &&filename);

    void sendGameState(const GameState &gameState);

    void sendChatMessage(std::string &&message,
                         std::string &&nickname);

    void disconnect();

    ~GameServerSocket();
};

#endif //TP4_TALLER_GAME_SERVER_SOCKET_H
