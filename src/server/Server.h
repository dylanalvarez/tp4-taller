#ifndef TOWERDEFENSE_SERVER_H
#define TOWERDEFENSE_SERVER_H


#include <mutex>
#include "../common/Thread.h"
#include "../common/ServerSocket.h"
#include "Match.h"

class Server : public Thread {
public:
    explicit Server(const std::string &port);

    ~Server() override;

    // cuando el server se inicia comienza a aceptar clientes
    // y los distribuye por las distintas partidas
    void run() override;

    void joinMatch(Client &client, int match_id);

    // retorna el id de la partida
    int createMatch(Client &client, int map_id, const std::string &match_name);

    void addElementToPlayer(const Client &, int match_id,
                            const std::string &element);

    void startMatch(int match_id);

    // añade un mapa al servidor
    // Pre: el server no esta corriendo
    // para añadir un mapa se debe detener el server
    void addMap(const std::string &file_path);

    // añade todos los clientes del vector a la lista 
    // de espera "clients_waiting_for_match"
    void addClientsToWaitingList(std::vector<Client *> &clients);

    void stop();

    Server(const Server &) = delete;

    Server &operator=(const Server &) = delete;

    Server(Server &&) = delete;

    Server &operator=(Server &&) = delete;

private:
    std::mutex mutex;
    ServerSocket accept_socket;
    std::map<int, Match *> matchs;
    std::vector<Client *> clients_waiting_for_match;

    std::vector<Communication::NameAndID> matchs_id;
    std::vector<Communication::NameAndID> maps;

    int map_id;
    int match_id;
    std::map<int, const std::string> maps_paths;

    const std::string config_file_path = "../Resources/config.yaml";

    void cleanMatchs();

    void cleanClients();

    // vuelve a enviar los mapas y partidas
    // disponibles a los clientes sin partida
    void reSeanInitialData();
};


#endif //TOWERDEFENSE_SERVER_H
