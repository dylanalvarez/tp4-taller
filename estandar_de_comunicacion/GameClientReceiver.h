#ifndef TP4_TALLER_GAME_CLIENT_RECEIVER_H
#define TP4_TALLER_GAME_CLIENT_RECEIVER_H

#include "CommunicationUtils.h"
#include "../client-server/common_Socket.h"

class GameClientReceiver {
public:
    GameClientReceiver(Socket& socket);

    void getInitialData(const std::vector<Communication::NameAndID> &matches,
                         const std::vector<Communication::NameAndID> &maps);

    // map will be the raw YAML file content
    void getMap(std::string &&map);

    void getGameState(const Communication::GameState &gameState);

    void getChatMessage(std::string &&message,
                         std::string &&nickname);

    ~GameClientReceiver();
};

#endif //TP4_TALLER_GAME_CLIENT_RECEIVER_H
