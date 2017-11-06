//
// Created by facundo on 27/10/17.
//

#include <syslog.h>
#include <fstream>
#include <iostream>
#include "Server.h"
#include "../common/AcceptFailedException.h"

Server::Server(const std::string& port) : accept_socket(port) {
    map_id = 0;
    match_id = 0;
    maps_paths.emplace(map_id++, "mapa_inicial.yaml");
}

Server::~Server() {
    for (auto& match : matchs) {
        if (match.second->hasStarted()) { match.second->join(); }
        delete match.second;
    }
}

void Server::run() {
    while (accept_socket.canAccept()) {
        try {
            Socket new_client = accept_socket.accept();
            // se pudo cerrar el socket en el accept
            auto* client = new Client(std::move(new_client), matchs_id, maps, *this);
            clients.push_back(client);
            client->start();
            //TODO clean clients
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
    for (Client* client : clients) {
        // clientes que no estan en una partida
        client->stop();
        delete client;
    }
}

void Server::joinMatch(Client& client, int id) {
    std::lock_guard<std::mutex> lock(mutex);

    try {
        Match* match = matchs.at(id);
        match->addPlayer(&client);
        clients.erase(std::remove(clients.begin(), clients.end(), &client));
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
            std::cerr << "Error: El mapa ya fue agregado\n";
            return;
        }
    }

    maps_paths.emplace(map_id, file_path);
    Communication::NameAndID new_map;
    new_map.id = map_id++;
    new_map.name = YAML::LoadFile(file_path)["name"].as<std::string>();
    maps.push_back(std::move(new_map));
    std::cout << "Mapa agreado con exito!\n";
}

void Server::startMatch(int match_id) {
    std::lock_guard<std::mutex> lock(mutex);

    if (matchs.at(match_id)->hasStarted()) { return; }

    try {
        matchs.at(match_id)->start();
    } catch (std::exception& e) {
        // el match no existe
        // enviar error al cliente
    }
}

int Server::createMatch(Client &client, int map_id) {
    std::lock_guard<std::mutex> lock(mutex);

    try {
        auto* match = new Match(config_file_path, maps_paths.at(map_id), match_id);
        matchs.emplace(match_id, match);
        matchs.at(match_id)->addPlayer(&client);
        clients.erase(std::remove(clients.begin(), clients.end(), &client));

        Communication::NameAndID new_match_;
        new_match_.id = match_id;
        new_match_.name = matchs.at(match_id)->getGame()->getGameName();
        matchs_id.push_back(std::move(new_match_));
    } catch (std::out_of_range& e) {
        // el mapa no existe
        // enviar error al cliente
    }
    return match_id++;
}
