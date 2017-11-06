#include "emisor.h"

/*Emisor::Emisor(GameClientReceiver &receiver, Socket &&socket): socket(receiver, socket){
}*/

void Emisor::iniciar(){
  /*Mensaje aux;
  while (seguir) {
    if (siguiente) {
      siguiente=false;
      cola.tomarNuevoTermino(&aux);
      switch (aux.tipo) {
        case Mensaje::Type::chooseTeam:
          printf("chooseTeam\n");
        break;
        case Mensaje::Type::chooseMap:
          printf("chooseMap\n");
        break;
        case Mensaje::Type::chooseElement:
          printf("chooseElement\n");
        break;
        case Mensaje::Type::sendChatMessage:
          printf("sendChatMessage\n");
        break;
        case Mensaje::Type::pingTile:
          printf("pingTile\n");
        break;
        case Mensaje::Type::applySpell1:
          printf("applySpell1\n");
        break;
        case Mensaje::Type::applySpell2:
          printf("applySpell2\n");
        break;
        case Mensaje::Type::applyUpgrade:
          printf("applyUpgrade\n");
        break;
        case Mensaje::Type::buildTower:
          printf("buildTower\n");
        break;
      }
    }
  }*/
}

void Emisor::elegirEquipo(std::string &nickname, int teamID){
  /*Mensaje aux;
  aux.tipo = Mensaje::Type::chooseTeam;
  aux.elString = nickname;
  aux.elInt1 = teamID;
  cola.agregarLinea(aux);*/
}
void Emisor::elegirMapa(std::string &nickname, int mapID){
  /*Mensaje aux;
  aux.tipo = Mensaje::Type::chooseMap;
  aux.elString = nickname;
  aux.elInt1 = mapID;
  cola.agregarLinea(aux);*/
}
void Emisor::elegirElemento(Communication::Element elemento){
  /*Mensaje aux;
  aux.tipo = Mensaje::Type::chooseElement;
  aux.elElemento = elemento;
  cola.agregarLinea(aux);*/
}
void Emisor::enviarMensajeDeChat(std::string &mensaje){
  /*Mensaje aux;
  aux.tipo = Mensaje::Type::chooseElement;
  aux.elString =  mensaje;
  cola.agregarLinea(aux);*/
}
void Emisor::pingear(int x, int y){
  /*Mensaje aux;
  aux.tipo = Mensaje::Type::pingTile;
  aux.elInt1 = x;
  aux.elInt1 = y;
  cola.agregarLinea(aux);*/
}
void Emisor::lansarEchizo(Communication::PositionalPower poder){
  /*Mensaje aux;
  aux.tipo = Mensaje::Type::applySpell1;
  aux.elPoderPosicional = poder;
  cola.agregarLinea(aux);*/
}
void Emisor::lansarEchizo(Communication::TargetPower poder){
  /*Mensaje aux;
  aux.tipo = Mensaje::Type::applySpell2;
  aux.elPoderTargetado = poder;
  cola.agregarLinea(aux);*/
}
void Emisor::upgraTorre(Communication::Upgrade upgrade){
  /*Mensaje aux;
  aux.tipo = Mensaje::Type::applyUpgrade;
  aux.laMejora = upgrade;
  cola.agregarLinea(aux);*/
}
void Emisor::cosntruirTorre(int x, int y, Communication::Tower::Type tipo){
  /*Mensaje aux;
  aux.tipo = Mensaje::Type::buildTower;
  aux.elInt1 = x;
  aux.elInt1 = y;
  cola.agregarLinea(aux);*/
}


bool Emisor::siclo(){
  siguiente = true;
  return true;
}

void Emisor::terminar(){
  seguir = false;
  cola.finDeLista();
}
