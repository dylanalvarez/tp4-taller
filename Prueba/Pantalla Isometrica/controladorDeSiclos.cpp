#include "controladorDeSiclos.h"
#include <thread>

void ControladorDeSiclos::iniciar(){
  while (seguir) {
    std::this_thread::sleep_for (std::chrono::seconds(1));
     pulso.emit();
  }
}

void ControladorDeSiclos::terminar(){
  seguir = false;
}

ControladorDeSiclos::type_pulso ControladorDeSiclos::getPulso()
{
  return pulso;
}
