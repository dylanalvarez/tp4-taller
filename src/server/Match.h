//
// Created by facundo on 27/10/17.
//

#ifndef TOWERDEFENSE_MATCH_H
#define TOWERDEFENSE_MATCH_H


#include "../common/Thread.h"
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

    void startGame();

    void stop();

    void addPlayer(Client* client);
    void addElementToClient(const Client& client_to_add,
                            const std::string& element);
    int getID() const;
    bool hasStarted() const;
    bool isRunning() const;

    Match(const Match&) = delete;
    Match(Match&&) = delete ;
    Match& operator=(const Match&) = delete;
    Match& operator=(Match&&) = delete;

private:
    QueueProtected actions_queue;

    HordeCreator horde_creator;

    std::vector<Client*> clients;
    TowerDefenseGame game;
    Context context;

    int id;
    bool has_started;
    bool keep_running;

    const std::string& map;

    void cleanClients();
    
    const unsigned int time_step = 15000; // 15 milisegundos;
};


#endif //TOWERDEFENSE_MATCH_H
