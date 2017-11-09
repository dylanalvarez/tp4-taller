#include "receptor.h"

//receptor
Receptor::Receptor(GameClientReceiver& reciver, GameClientSocket& socket):
      reciver(reciver), socket(socket){
}
void Receptor::iniciar(){
  socket.run();
}
void Receptor::terminar(){
  socket.disconnect();
  seguir = false;
}
GameClientReceiver& Receptor::getReciver(){
  return reciver;
}
