#include "receptor.h"

//receptor
Receptor::Receptor(GameClientReceiver& reciver, GameClientSocket& socket):
      reciver(reciver), socket(socket){
}
void Receptor::iniciar(){
  socket.start();
}
void Receptor::terminar(){
  socket.join();
  seguir = false;
}
GameClientReceiver& Receptor::getReciver(){
  return reciver;
}
