//
// Created by facundo on 27/10/17.
//

#include "Client.h"

Client::Client(Socket &&socket, TowerDefenseGame& game) :
        socket(socket), game(game) {}

Client::~Client() = default;

void Client::run() {
    /** int opcode = receiver.getOpcode()
     *  switch(opcode) {
     *      case 7:
     *          receiver.getSpell(...);
     *          game.throwSpell(...)
     *          break;
     *       .
     *       .
     *       .
     *  }
     */
}
