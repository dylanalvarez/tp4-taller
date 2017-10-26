#ifndef TP4_TALLER_GAME_CLIENT_RECEIVER_H
#define TP4_TALLER_GAME_CLIENT_RECEIVER_H

#include "CommunicationUtils.h"

class GameClientReceiver {
public:
    GameClientReceiver();

    void sendInitialData(const std::vector<NameAndID> &matches,
                         const std::vector<NameAndID> &maps);

    // map will be the raw YAML file content
    void sendMap(std::string &&map);

    void sendGameState(const GameState &gameState);

    void sendChatMessage(std::string &&message,
                         std::string &&nickname);

    ~GameClientReceiver();
};

#endif //TP4_TALLER_GAME_CLIENT_RECEIVER_H
