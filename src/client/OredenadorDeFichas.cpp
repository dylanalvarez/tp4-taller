#include "OrdenadorDeFichas.h"
#define error 0

void OrdenadorDeFichas::ejecutarSicloDeAnimacion(){
  for (auto it = terreno.begin(); it != terreno.end(); ++it){
    it->second.ejecutarSicloDeAnimacion();
  }
  for (auto it = torres.begin(); it != torres.end(); ++it){
    it->second.ejecutarSicloDeAnimacion();
  }
  for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
    if (it->second.siguesVivo()) {
      enemigos.erase (it);
    }
  }
  for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
    it->second.ejecutarSicloDeAnimacion();
  }
  //primero vorra los efectos viejos
  for (auto it = poderes.begin(); it != poderes.end(); ++it){
    if (it->second.siguesVivo()) {
      poderes.erase (it);
    }
  } //ahora sigo
  for (auto it = poderes.begin(); it != poderes.end(); ++it){
    it->second.ejecutarSicloDeAnimacion();
  }
  for (auto it = portales.begin(); it != portales.end(); ++it){
    it->ejecutarSicloDeAnimacion();
  }
}

void OrdenadorDeFichas::preprarParaActualizacion(){
  for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
    it->second.setDestrulleme(true);
  }
}
//terreno
void OrdenadorDeFichas::agregarTerreno(FichaTerreno nuevaFicha){
  terreno.emplace(std::make_pair(nuevaFicha.getId(),nuevaFicha));
}
void OrdenadorDeFichas::imprimirTerreno(const Cairo::RefPtr<Cairo::Context>& cr,
                      DatosPantalla datosActuales){
  for (auto it = terreno.begin(); it != terreno.end(); ++it){
    it->second.dibujar(cr,datosActuales);
  }
}
int OrdenadorDeFichas::ObetenerTerrenoEnEstaPosicion(int x, int y){
  for (auto it = terreno.begin(); it != terreno.end(); ++it){
    if (it->second.colisionaConmigo(x,y)) {
      return it->first;
    }
  }
  return error;
}
FichaTerreno& OrdenadorDeFichas::getTerreno(int id){
  return terreno.at(id);
}


//torres
void OrdenadorDeFichas::agregarTorre(FichaTorre nuevaFicha){
  torres.emplace(std::make_pair(nuevaFicha.getId(),nuevaFicha));
}
void OrdenadorDeFichas::imprimirTorres(const Cairo::RefPtr<Cairo::Context>& cr,
                      DatosPantalla datosActuales){
  for (auto it = torres.begin(); it != torres.end(); ++it){
    it->second.dibujar(cr,datosActuales);
  }
}
int OrdenadorDeFichas::ObetenerTorreEnEstaPosicion(int x, int y){
  for (auto it = torres.begin(); it != torres.end(); ++it){
    if (it->second.colisionaConmigo(x,y)) {
      return it->first;
    }
  }
  return 0;
}

FichaTorre& OrdenadorDeFichas::getTorre(int id){
  return torres.at(id);
}

//Enemigo
void OrdenadorDeFichas::agregarEnemigo(FichaEnemigo nuevaFicha){
  enemigos.emplace(std::make_pair(nuevaFicha.getId(),nuevaFicha));
  if (idEnemigo < nuevaFicha.getId()) {
    idEnemigo = nuevaFicha.getId();
  }
}
void OrdenadorDeFichas::imprimirEnemigo(const Cairo::RefPtr<Cairo::Context>& cr,
                       DatosPantalla datosActuales){
  for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
    it->second.dibujar(cr,datosActuales);
  }
}
int OrdenadorDeFichas::ObetenerEnemigoEnEstaPosicion(int x, int y){
  for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
    if (it->second.colisionaConmigo(x,y)) {
      return it->first;
    }
  }
  return 0;
}
FichaEnemigo& OrdenadorDeFichas::getEnemigo(int id){
  return enemigos.at(id);
}
void OrdenadorDeFichas::actualizarEnemigo(Communication::Enemy actualzacion){
  if (idEnemigo < actualzacion.id) {
    agregarEnemigo(FichaEnemigo(actualzacion, sprites));
  }else{
    enemigos.at(actualzacion.id).actualizar(actualzacion);
  }
}


//efecto
void OrdenadorDeFichas::agregarEfectos(int inicio, int objetivo,
   int id2, VectorDeSprites &sprites){
  FichaEfectos nuevaFicha = FichaEfectos(getTorre(inicio), 1, sprites, getEnemigo(objetivo));
  poderes.emplace(std::make_pair(nuevaFicha.getId(),nuevaFicha));
}
void OrdenadorDeFichas::agregarEfectos(FichaEfectos nuevaFicha){
  poderes.emplace(std::make_pair(nuevaFicha.getId(),nuevaFicha));
}
void OrdenadorDeFichas::imprimirEfectos(const Cairo::RefPtr<Cairo::Context>& cr,
                      DatosPantalla datosActuales){
 for (auto it = poderes.begin(); it != poderes.end(); ++it){
   it->second.dibujar(cr,datosActuales);
 }
}

//Portal
void OrdenadorDeFichas::agregarPortal(FichaPortal nuevaFicha){
  portales.push_back(nuevaFicha);
}
void OrdenadorDeFichas::imprimirPortal(const Cairo::RefPtr<Cairo::Context>& cr,
                      DatosPantalla datosActuales){
  for (auto it = portales.begin(); it != portales.end(); ++it){
    it->dibujar(cr,datosActuales);
  }
}