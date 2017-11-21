#include "GestionadorDeSonidos.h"


void GestionadorDeSonidos::iniciar(){
  haySonido = false;
  seguir = true;
  while (seguir) {
    if (haySonido) {
      haySonido = false;
      reprorduicrSonid();
    }
  }
}
void GestionadorDeSonidos::reprorduicrSonid(){
  Sound sound(proximoSonido);
  sound.start();
  sound.join();
}
void GestionadorDeSonidos::terminar(){
  seguir = false;
}
void GestionadorDeSonidos::siguienteSonido(std::string nuevoSonido){
  proximoSonido = nuevoSonido;
  haySonido = true;
}
