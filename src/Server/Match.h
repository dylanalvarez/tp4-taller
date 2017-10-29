//
// Created by facundo on 27/10/17.
//

#ifndef TOWERDEFENSE_MATCH_H
#define TOWERDEFENSE_MATCH_H


#include "Thread.h"
#include "../model/TowerDefenseGame.h"

class Match : public Thread {
public:
    Match(const std::string& config_file_path,
          const std::string& map_file_path);

    ~Match() override;

    void run() override;

    Match(const Match&) = delete;
    Match(Match&&) = delete;
    Match& operator=(const Match&) = delete;
    Match& operator=(Match&&) = delete;

private:
    // en micro segundos
    const unsigned int time_step = 15000; // 15 milisegundos;

    TowerDefenseGame game;
};


#endif //TOWERDEFENSE_MATCH_H
