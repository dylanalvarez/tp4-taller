#include "GestionadorDeSonidos.h"
#include "VectorDeSprites.h"


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
  if (haySonido){
    if (proximoSonido == (std::string(SonidoMatarMonstruo)))
      return;
    if ((proximoSonido == (std::string(SonidoNuevoMonstruo)))&&
                  (nuevoSonido == (std::string(SonidoNuevoAtaque))))
      return;
  }
  proximoSonido = nuevoSonido;
  haySonido = true;
}
