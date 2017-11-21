#include "emisor.h"
#include "../common/GameClientSocket.h"
#include "../common/CommunicationUtils.h"
#include "../common/Exception.h"

/*Emisor::Emisor(GameClientReceiver &receiver, Socket &&socket): socket(receiver, socket){
}*/
void Emisor::cargarSocket(GameClientSocket* socket2){
  socket = socket2;
}

void Emisor::iniciar(){
  Mensaje aux;
  while (seguir){
    cola.tomarNuevoTermino(&aux);
    switch (aux.tipo) {
      case Mensaje::Type::chooseTeam:
        printf("chooseTeam\n");
        socket->chooseTeam(std::move(aux.elString),aux.elInt1);
      break;
      case Mensaje::Type::chooseMap:
        printf("chooseMap\n");
        socket->chooseMap(std::move(aux.elString),std::move(aux.elString2),aux.elInt1);
      break;
      case Mensaje::Type::chooseElement:
        printf("chooseElement\n");
        socket->chooseElement(Communication::to_element(aux.elString));
      break;
      case Mensaje::Type::sendChatMessage:
        printf("sendChatMessage\n");
        socket->sendChatMessage(std::move(aux.elString));
      break;
      case Mensaje::Type::pingTile:
        printf("pingTile\n");
        socket->pingTile(aux.elInt1,aux.elInt2);
      break;
      case Mensaje::Type::applySpell1:
        printf("applySpell1\n");
        socket->applySpell(Communication::PositionalPower(aux.elString,
          aux.elInt1,aux.elInt2));
      break;
      case Mensaje::Type::applySpell2:
        printf("applySpell2\n");
        socket->applySpell(Communication::TargetPower(aux.elString, aux.elInt1));
      break;
      case Mensaje::Type::applyUpgrade:
        printf("applyUpgrade\n");
        socket->applyUpgrade(Communication::Upgrade(aux.elString,aux.elInt1));
      break;
      case Mensaje::Type::buildTower:
        printf("buildTower\n");
        socket->buildTower(aux.elInt1, aux.elInt2,
          Communication::Tower::string_to_type(aux.elString));
      break;
      case Mensaje::Type::startGame:
        printf("startGame\n");
            try{
              socket->startGame();
            } catch (Exception& e) {}
      break;
      }
  }
}

void Emisor::elegirEquipo(std::string nickname, int teamID){
  Mensaje aux;
  aux.tipo = Mensaje::Type::chooseTeam;
  aux.elString = nickname;
  aux.elInt1 = teamID;
  cola.agregarLinea(aux);
}
void Emisor::elegirMapa(std::string nickname, std::string mapName, int mapID){
  Mensaje aux;
  aux.tipo = Mensaje::Type::chooseMap;
  aux.elString = nickname;
  aux.elString2 = mapName;
  aux.elInt1 = mapID;
  cola.agregarLinea(aux);
}
void Emisor::elegirElemento(std::string tipo){
  Mensaje aux;
  aux.tipo = Mensaje::Type::chooseElement;
  aux.elString = tipo;
  cola.agregarLinea(aux);
}
void Emisor::empesarJuego(){
  Mensaje aux;
  aux.tipo = Mensaje::Type::startGame;
  cola.agregarLinea(aux);
}
void Emisor::enviarMensajeDeChat(std::string mensaje){
  Mensaje aux;
  aux.tipo = Mensaje::Type::sendChatMessage;
  aux.elString =  mensaje;
  cola.agregarLinea(aux);
}
void Emisor::pingear(int x, int y){
  Mensaje aux;
  aux.tipo = Mensaje::Type::pingTile;
  aux.elInt1 = x;
  aux.elInt2 = y;
  cola.agregarLinea(aux);
}
void Emisor::lansarEchizo(int x, int y, std::string tipo){
  Mensaje aux;
  aux.tipo = Mensaje::Type::applySpell1;
  aux.elString = tipo;
  aux.elInt1 = x;
  aux.elInt2 = y;
  cola.agregarLinea(aux);
}
void Emisor::lansarEchizo(int id, std::string tipo){
  Mensaje aux;
  aux.tipo = Mensaje::Type::applySpell2;
  aux.elString = tipo;
  aux.elInt1 = id;
  cola.agregarLinea(aux);
}
void Emisor::upgraTorre(int id, std::string tipo){
  Mensaje aux;
  aux.tipo = Mensaje::Type::applyUpgrade;
  aux.elInt1 = id;
  aux.elString = tipo;
  cola.agregarLinea(aux);
}
void Emisor::cosntruirTorre(int x, int y, std::string tipo){
  Mensaje aux;
  aux.tipo = Mensaje::Type::buildTower;
  aux.elString = tipo;
  aux.elInt1 = x;
  aux.elInt2 = y;
  cola.agregarLinea(aux);
}


bool Emisor::siclo(){
  siguiente = true;
  return true;
}

void Emisor::terminar(){
  seguir = false;
  cola.finDeLista();
}
