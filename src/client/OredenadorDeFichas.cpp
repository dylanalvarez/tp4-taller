#include "OrdenadorDeFichas.h"
#define error 0

void OrdenadorDeFichas::ejecutarSicloDeAnimacion(){
  std::unique_lock<std::mutex> lck(m);
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
void OrdenadorDeFichas::imprir(const Cairo::RefPtr<Cairo::Context>& cr,
                     DatosPantalla datosActuales){
    std::unique_lock<std::mutex> lck(m);
    imprimirTerreno(cr,datosActuales);
    imprimirPortal(cr,datosActuales);
    imprimirEnemigo(cr,datosActuales);
    imprimirTorres(cr,datosActuales);
    imprimirEfectos(cr,datosActuales);
}
void OrdenadorDeFichas::actualizar(const Communication::GameState &gameState){
  std::unique_lock<std::mutex> lck(m);
  preprarParaActualizacion();
  for (auto it = gameState.enemies.begin() ; it != gameState.enemies.end(); ++it)
    actualizarEnemigo(*it);
  for (auto it = gameState.towers.begin() ; it != gameState.towers.end(); ++it)
    actualizarTorre(*it);
/*  for (auto it = aux.positionalPowers.begin() ; it != aux.positionalPowers.end(); ++it)
    fichas.actualizarEnemigo(*it);
  for (auto it = aux.targetPowers.begin() ; it != aux.targetPowers.end(); ++it)
    fichas.actualizarEnemigo(*it);
*/
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
void OrdenadorDeFichas::actualizarTorre(Communication::Tower actualzacion){
  printf("actualizar\n");
  if (idEnemigo < actualzacion.id) {
    agregarTorre(FichaTorre(actualzacion, sprites));
  }else{
    torres.at(actualzacion.id).actualizar(actualzacion);
  }
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
