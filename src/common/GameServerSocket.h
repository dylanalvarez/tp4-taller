#ifndef TP4_TALLER_GAME_SERVER_SOCKET_H
#define TP4_TALLER_GAME_SERVER_SOCKET_H

#include <string>
#include <mutex>
#include "GameServerReceiver.h"
#include "Thread.h"

class GameServerReceiver;

class GameServerSocket : public Thread {
public:
    // When it recieves a message, it will invoke a method in the receiver.
    GameServerSocket(GameServerReceiver& receiver, Socket&& socket);

    void run() override;

    void sendInitialData(const std::vector<Communication::NameAndID> &matches,
                         const std::vector<Communication::NameAndID> &maps);

    void makeElementUnavailable(Communication::Element element,
                                const std::string &username);

    // Filename relative to executable
    void sendMap(const std::string &filename);

    void sendGameState(const Communication::GameState &gameState);

    void sendChatMessage(const std::string &message,
                         const std::string &nickname);

    void sendPing(int x, int y);

    void disconnect();
    
    bool isOperational() const;

    ~GameServerSocket() override;

    GameServerSocket(const GameServerSocket&) = delete;
    GameServerSocket& operator=(const GameServerSocket&) = delete;
    GameServerSocket(GameServerSocket&&) noexcept;

private:
    // el socket es un recurso compartido
    // lo puede acceder el cliente pidiendo que se envie un mensaje
    // y lo puede acceder el thread match enviando el estado del juego
    GameServerReceiver& receiver;
    Socket socket;
    bool keep_running;

    void handleChosenMap(std::string& yaml);
    void handleChosenMatch(std::string& yaml);
    void handleChosenElement(std::string& yaml);
    void handleSendMessage(std::string& yaml);
    void handlePingTile(std::string& yaml);
    void handleSpell(std::string& yaml);
    void handleUpgrade(std::string& yaml);
    void handleBuildTower(std::string& yaml);
    void sendNode(YAML::Node& node);
};

#endif //TP4_TALLER_GAME_SERVER_SOCKET_H
