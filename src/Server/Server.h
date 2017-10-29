//
// Created by facundo on 27/10/17.
//

#ifndef TOWERDEFENSE_SERVER_H
#define TOWERDEFENSE_SERVER_H


#include <mutex>
#include "Thread.h"
#include "../../client-server/server_ServerSocket.h"
#include "Match.h"

class Server : public Thread {
public:
    explicit Server(const std::string& port);
    ~Server() override;

    // cuando el server se inicia comienza a aceptar clientes
    // y los distribuye por las distintas partidas
    void run() override;

    Match& joinToMatch(Client& client, int match_id, bool is_creating);

    // añade un mapa al servidor
    // Pre: el server no esta corriendo
    // para añadir un mapa se debe detener el server
    void addMap(const std::string& file_path);

    void stop();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;

private:
    ServerSocket accept_socket;
    std::map<int, Match> matchs;
    std::vector<Client> connecting_client_list;

    std::vector<Communication::NameAndID> matchs_id;
    std::vector<Communication::NameAndID> maps;

    int map_id;
    int match_id;
    std::map<int, const std::string> maps_paths;

    const std::string config_file_path = "config.yaml";
};


#endif //TOWERDEFENSE_SERVER_H