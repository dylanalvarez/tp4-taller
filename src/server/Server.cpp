//
// Created by facundo on 27/10/17.
//

#include <syslog.h>
#include <fstream>
#include "Server.h"
#include "../common/AcceptFailedException.h"

Server::Server(const std::string& port) : accept_socket(port) {
    map_id = 0;
    match_id = 0;
    maps_paths.emplace(map_id, "mapa_inicial.yaml");
}

Server::~Server() {
    for (auto& match : matchs) {
        match.second->join();
        delete match.second;
    }
}

void Server::run() {
    while (accept_socket.canAccept()) {
        try {
            Socket new_client = accept_socket.accept();
            // se pudo cerrar el socket en el accept
            auto* client = new Client(std::move(new_client), matchs_id, maps, *this);
            client->start();
            clients.push_back(client);
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
}

Match& Server::joinMatch(Client& client, int id, bool is_creating) {
    std::lock_guard<std::mutex> lock(mutex);

    if (is_creating) {
        try {
            auto* match = new Match(config_file_path, maps_paths.at(id), match_id);
            matchs.emplace(match_id, match);
            matchs.at(match_id)->addPlayer(&client);
            std::remove(clients.begin(), clients.end(), &client);

            Communication::NameAndID new_match_;
            new_match_.id = match_id;
            new_match_.name = YAML::LoadFile(maps_paths.at(id))["name"].as<std::string>();
            matchs_id.push_back(std::move(new_match_));
            return *matchs.at(match_id++);
        } catch (std::out_of_range& e) {
            // el mapa no existe
            // enviar error al cliente
        }
    }
    // se esta uniendo
    Match* match = matchs.at(id);
    match->addPlayer(&client);
    std::remove(clients.begin(), clients.end(), &client);
    return *match;
}

void Server::addMap(const std::string& file_path) {
    try {
        YAML::LoadFile(file_path);
    } catch (YAML::BadFile& e) {
        syslog(LOG_CRIT, "Error en el archivo: %s\n%s\n", file_path.c_str(), e.what());
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
        matchs.at(match_id)->start();
    } catch (std::exception& e) {
        // el match no existe
        // enviar error al cliente
    }
}
