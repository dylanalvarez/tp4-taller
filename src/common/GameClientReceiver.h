#ifndef TP4_TALLER_GAME_CLIENT_RECEIVER_H
#define TP4_TALLER_GAME_CLIENT_RECEIVER_H

#include <yaml-cpp/yaml.h>
#include "Socket.h"
#include "CommunicationUtils.h"
#include "../client/menuTorres.h"
#include "../client/OrdenadorDeFichas.h"

class GameClientReceiver {
    OrdenadorDeFichas& fichas;
    MenuTorres& menues;
public:
    //GameClientReceiver(Socket& socket);
    GameClientReceiver(OrdenadorDeFichas& fichas2, MenuTorres& menues2);

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
