#ifndef TP4_TALLER_GAME_SERVER_SOCKET_H
#define TP4_TALLER_GAME_SERVER_SOCKET_H

#include <string>
#include <mutex>
#include "CommunicationUtils.h"
#include "GameServerReceiver.h"

class GameServerSocket {
public:
    // When it recieves a message, it will invoke a method in the receiver.
    GameServerSocket(GameServerReceiver& receiver, Socket&& socket);

    void sendInitialData(const std::vector<Communication::NameAndID> &matches,
                         const std::vector<Communication::NameAndID> &maps);

    // Filename relative to executable
    void sendMap(std::string &&filename);

    void sendGameState(const Communication::GameState &gameState);

    void sendChatMessage(std::string &&message,
                         std::string &&nickname);

    void disconnect();

    ~GameServerSocket();

    GameServerSocket(GameServerSocket&&) noexcept ;
    GameServerSocket operator=(GameServerSocket&&) noexcept ;

private:
    std::string _toFixedLengthString(long messageLength, int length);

    // el socket es un recurso compartido
    // lo puede acceder el cliente pidiendo que se envie un mensaje
    // y lo puede acceder el thread match enviando el estado del juego
    GameServerReceiver& receiver;
    Socket socket;
};

#endif //TP4_TALLER_GAME_SERVER_SOCKET_H
