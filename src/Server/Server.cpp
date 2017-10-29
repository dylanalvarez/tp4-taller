//
// Created by facundo on 27/10/17.
//

#include "Server.h"

Server::Server(const std::string& port) : accept_socket(port) {
    map_id = 0;
}

Server::~Server() {
    for (auto& match : matchs) {
        match.second.join();
    }
}

void Server::run() {
    while (accept_socket.canAccept()) {
        Socket new_client = accept_socket.accept();
        if (accept_socket.canAccept()) {
            // se pudo cerrar el socket en el accept
            Client client(std::move(new_client), matchs_id, maps, *this);
            connecting_client_list.push_back(std::move(client));
        }
    }
}

void Server::stop() {
    accept_socket.shutdown();
}

Match& Server::joinToMatch(Client &client, int id, bool is_creating) {
    std::lock_guard<std::mutex> lock(mutex);
    if (is_creating) {
        try {
           Match new_match(maps_paths.at(id), config_file_path, match_id);
           new_match.addPlayer(std::move(client));
           new_match.start();
           matchs.emplace(match_id, std::move(new_match));
           return matchs.at(match_id++);
       } catch (std::out_of_range& e) {
           // el mapa no existe
       }
    }
    // se esta uniendo
    Match& match = matchs.at(id);
    match.addPlayer(std::move(client));
    return match;
}

void Server::addMap(const std::string& file_path) {
    maps_paths.emplace(map_id++, file_path);
}
