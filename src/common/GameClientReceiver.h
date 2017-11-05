#ifndef TP4_TALLER_GAME_CLIENT_RECEIVER_H
#define TP4_TALLER_GAME_CLIENT_RECEIVER_H

#include "CommunicationUtils.h"
#include "Socket.h"

class GameClientReceiver {
public:
    //GameClientReceiver(Socket& socket);
    GameClientReceiver();

    void getInitialData(const std::vector<Communication::NameAndID> &matches,
                         const std::vector<Communication::NameAndID> &maps);

    // map will be the raw YAML file content
    void getMap(std::string &&map);

    void getGameState(const Communication::GameState &gameState);

    void getChatMessage(std::string &&message,
                         std::string &&nickname);

    // notificar con que elemento te quedaste O
    // cual dejo de ser disponible para seleccion

    ~GameClientReceiver();
};

#endif //TP4_TALLER_GAME_CLIENT_RECEIVER_H
