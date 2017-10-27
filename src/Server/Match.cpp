//
// Created by facundo on 27/10/17.
//

#include "Match.h"

Match::Match(const std::string &config_file_path,
             const std::string &map_file_path) :
                game(config_file_path, map_file_path) {}

Match::~Match() = default;

void Match::run() {
    while(!game.isGameOver()) {
        game.updateGame();
        /** enviar el estado del juego */
        usleep(time_step);
    }
}
