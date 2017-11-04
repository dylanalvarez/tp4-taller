#include "fListaDeDosLectores.h"
#include <string>

#define ok 0
#define fin 1

ColaBloqueante::ColaBloqueante(){
  finalizado = false;
}

int ColaBloqueante::agregarLinea(Mensaje entrada){
  std::unique_lock<std::mutex> lck(m);
  lista.push_front(entrada);
  ready = true;
  cv.notify_all();
  return ok;
}

int ColaBloqueante::finDeLista(){
  std::unique_lock<std::mutex> lck(m); //sacado de cplusplus
  ready = true;
  finalizado = true;
  cv.notify_all();
  return ok;
}

int ColaBloqueante::tomarNuevoTermino(Mensaje* salida){
  std::unique_lock<std::mutex> lck(m);
  if (lista.size() == 0){
    if (finalizado) {
      return fin;
    }
    ready = false;
    while (!ready){
      cv.wait(lck);
    }
    if (lista.size() == 0)
      return fin;
  }
  *salida = lista.back();
  lista.pop_back();
  return ok;
}
