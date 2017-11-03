//
// Created by facundo on 27/10/17.
//

#ifndef TOWERDEFENSE_MATCH_H
#define TOWERDEFENSE_MATCH_H


#include "Thread.h"
#include "../model/TowerDefenseGame.h"
#include "Client.h"
#include "QueueProtected.h"
#include "HordeCreator.h"

class Match : public Thread {
public:
    Match(const std::string& config_file_path,
          const std::string& map_file_path, int id);

    ~Match() override;

    void run() override;

    void addPlayer(Client&& client);

    TowerDefenseGame* getGame();
    int getID() const;

    Match(const Match&) = delete;
    Match(Match&&) noexcept ;
    Match& operator=(const Match&) = delete;
    Match& operator=(Match&&) = delete;

private:
    HordeCreator horde_creator;

    std::mutex mutex;
    std::vector<Client> clients;
    QueueProtected actions_queue;
    TowerDefenseGame game;
    Context context;
    int id;
    bool has_started;

    // en micro segundos
    const unsigned int time_step = 15000; // 15 milisegundos;
};


#endif //TOWERDEFENSE_MATCH_H
