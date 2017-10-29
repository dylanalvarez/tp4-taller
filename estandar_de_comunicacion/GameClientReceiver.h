#ifndef TP4_TALLER_GAME_CLIENT_RECEIVER_H
#define TP4_TALLER_GAME_CLIENT_RECEIVER_H

#include "CommunicationUtils.h"

using Communication::GameState;
using Communication::NameAndID;

class GameClientReceiver {
public:
    GameClientReceiver();

    void getInitialData(const std::vector<NameAndID> &matches,
                         const std::vector<NameAndID> &maps);

    // map will be the raw YAML file content
    void getMap(std::string &&map);

    void getGameState(const GameState &gameState);

    void getChatMessage(std::string &&message,
                         std::string &&nickname);

    ~GameClientReceiver();
};

#endif //TP4_TALLER_GAME_CLIENT_RECEIVER_H
