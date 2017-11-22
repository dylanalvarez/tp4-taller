//
// Created by facundo on 27/10/17.
//

#include <syslog.h>
#include <fstream>
#include <iostream>
#include "Server.h"
#include "../common/AcceptFailedException.h"

Server::Server(const std::string& port) :
        accept_socket(port) {
    map_id = 0;
    match_id = 0;
}

Server::~Server() {
    for (auto& match : matchs) {
        if (match.second->hasStarted()) { match.second->join(); }
        delete match.second;
    }
    for (Client* client : clients_waiting_for_match) {
        delete client;
    }
}

void Server::run() {
    while (accept_socket.canAccept()) {
        try {
            Socket new_client = accept_socket.accept();
            // se pudo cerrar el socket en el accept
            cleanMatchs();
            auto* client = new Client(std::move(new_client), *this);

            std::lock_guard<std::mutex> lock(mutex);
            clients_waiting_for_match.push_back(client);

            client->start();
            client->sendInitialData(matchs_id, maps);
        } catch (AcceptFailedException& e) {
            // se cerro el socket
        }
    }
}

void Server::stop() {
    accept_socket.shutdown();
    for (auto &match : matchs) {
        match.second->stop();
    }
    for (Client* client : clients_waiting_for_match) {
        // clientes que no estan en una partida
        client->stop();
    }
}

void Server::joinMatch(Client& client, int id) {
    std::lock_guard<std::mutex> lock(mutex);

    try {
        Match *match = matchs.at(id);
        if (match->addPlayer(&client)) {
            clients_waiting_for_match.erase(std::remove(
                    clients_waiting_for_match.begin(), clients_waiting_for_match.end(), &client));
        }
    } catch (std::exception& e) {
        // la partida no existe
        // enviar error al cliente
    }
}

void Server::addMap(const std::string& file_path) {
    try {
        YAML::LoadFile(file_path);
    } catch (YAML::BadFile& e) {
        syslog(LOG_CRIT, "Error en el archivo: %s\n%s\n", file_path.c_str(), e.what());
        std::cerr << "Error al agregar mapa, ver syslog para mas informacion\n";
        return;
    }

    for (auto &maps_path : maps_paths) {
        if (maps_path.second == file_path) {
            return;
        }
    }

    maps_paths.emplace(map_id, file_path);
    Communication::NameAndID new_map;
    new_map.id = map_id++;
    new_map.name = YAML::LoadFile(file_path)["name"].as<std::string>();
    maps.push_back(std::move(new_map));
}

void Server::startMatch(int match_id) {
    std::lock_guard<std::mutex> lock(mutex);

    try {
        if (matchs.at(match_id)->hasStarted()) { return; }
        matchs.at(match_id)->startGame();

        for (auto it = matchs_id.begin(); it != matchs_id.end(); ++it) {
            if (it->id == match_id) {
                matchs_id.erase(it);
                break;
            }
        }
    } catch (std::exception& e) {
        // el match no existe
        // enviar error al cliente
    }
}

int Server::createMatch(Client &client, int map_id,
                        const std::string& match_name) {
    std::lock_guard<std::mutex> lock(mutex);

    try {
        auto* match = new Match(config_file_path, maps_paths.at(map_id),
                                match_id, *this);
        matchs.emplace(match_id, match);
        matchs.at(match_id)->addPlayer(&client);
        clients_waiting_for_match.erase(std::remove(clients_waiting_for_match.begin(),
                                                    clients_waiting_for_match.end(), &client));

        Communication::NameAndID new_match_;
        new_match_.id = match_id;
        new_match_.name = match_name;
        matchs_id.push_back(std::move(new_match_));
        reSeanInitialData();
    } catch (std::out_of_range& e) {
        syslog(LOG_CRIT, "Error: el mapa con id %d no existe\n", map_id);
        // el mapa no existe
        // enviar error al cliente
    } catch (YAML::BadFile& b) {
        syslog(LOG_CRIT, "Error en el archivo: %s\n%s",
               maps_paths.at(map_id).c_str(), b.what());
        std::cerr << "Error al crear la partida con el mapa " +
                maps_paths.at(map_id) + ", ver syslog para mas informacion";
        // enviar error al cliente
    }
    return match_id++;
}

void Server::addElementToPlayer(const Client& client, int match_id,
                                const std::string& element) {
    try {
        std::lock_guard<std::mutex> lock(mutex);
        matchs.at(match_id)->addElementToClient(client, element);
    } catch (std::exception& e) {
       // match inexistente
    }
}

void Server::cleanMatchs() {
    std::map<int, Match*> running_matchs;
    for (auto& match : matchs) {
        if (!match.second->isRunning()) {
            for (auto it = matchs_id.begin(); it != matchs_id.end(); ++it) {
                if (it->id == match.second->getID()) {
                    matchs_id.erase(it);
                    break;
                }
            }
            match.second->stop();
            if (match.second->hasStarted()) { match.second->join(); }
            delete match.second;
        } else {
            running_matchs.insert(match);
        }
    }
    std::swap(matchs, running_matchs);
}

void Server::reSeanInitialData() {
    for (Client* client: clients_waiting_for_match) {
        client->sendInitialData(matchs_id, maps);
    }
}

void Server::addClientsToWaitingList(std::vector<Client*>& clients) {
    std::lock_guard<std::mutex> lock(mutex);

    for (Client* client : clients) {
        client->reset();
        client->sendInitialData(matchs_id, maps);
        clients_waiting_for_match.push_back(client);
    }
}
