#include "OrdenadorDeFichas.h"
#include "../editor/Map.h"
#include <fstream>
#include <iostream>
#include <fstream>
#define error 0

void OrdenadorDeFichas::ejecutarSicloDeAnimacion(){
  std::unique_lock<std::mutex> lck(m);
  for (auto it = terreno.begin(); it != terreno.end(); ++it){
    it->second.ejecutarSicloDeAnimacion();
  }
  for (auto it = torres.begin(); it != torres.end(); ++it){
    it->second.ejecutarSicloDeAnimacion();
  }
  for (auto it = enemigos.cbegin(); it != enemigos.cend();) {
    if (it->second.siguesVivo()) { enemigos.erase(it++); } else { ++it; }
  }
  for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
    it->second.ejecutarSicloDeAnimacion();
  }
  for (auto it = poderes.cbegin(); it != poderes.cend();) {
    if (it->second.siguesVivo()) { poderes.erase(it++); } else { ++it; }
  }
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
  for (auto it = gameState.positionalPowers.begin() ; it != gameState.positionalPowers.end(); ++it)
    actualizarEfectos(*it);
  for (auto it = gameState.targetPowers.begin() ; it != gameState.targetPowers.end(); ++it)
    actualizarEfectos(*it);
  for (auto it = poderes.begin(); it != poderes.end(); ++it)
      it->second.ejecutarSicloDeActualizacion();
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
  if (idTorre < nuevaFicha.getId()) {
    idTorre = nuevaFicha.getId();
  }
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
  if (idTorre < actualzacion.id) {
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
void OrdenadorDeFichas::actualizarEfectos(Communication::PositionalPower actualzacion){
  idEfectos++;
  switch (actualzacion.type){
    case Communication::PositionalPower::Type::fissure:
    agregarEfectos(FichaEfectos(actualzacion.x, actualzacion.y, idEfectos,
       FichaGrieta, sprites));
    break;
    case Communication::PositionalPower::Type::terraforming:
    //printf("terraforameando, %i, %i\n", actualzacion.x, actualzacion.y);
      getTerreno(ObetenerTerrenoEnEstaPosicion(actualzacion.x, actualzacion.y)
    ).cambiarTipo(FichaPisoFirme, sprites);
    break;
    case Communication::PositionalPower::Type::meteorite:
    agregarEfectos(FichaEfectos(actualzacion.x, actualzacion.y, idEfectos,
       FichaMetorito, sprites));
    break;
    case Communication::PositionalPower::Type::fireWall:
    agregarEfectos(FichaEfectos(actualzacion.x, actualzacion.y, idEfectos,
       FichafireWall, sprites));
    break;
    case Communication::PositionalPower::Type::blizzard:
    agregarEfectos(FichaEfectos(actualzacion.x, actualzacion.y, idEfectos,
       FichaVentisca, sprites));
    break;
    case Communication::PositionalPower::Type::tornado:
    agregarEfectos(FichaEfectos(actualzacion.x, actualzacion.y, idEfectos,
       FichaTornado, sprites));
    break;
  }
}

void OrdenadorDeFichas::actualizarEfectos(Communication::TargetPower actualzacion){
  idEfectos++;
  switch (actualzacion.type){
    case Communication::TargetPower::Type::freezing:
    agregarEfectos(FichaEfectos(idEfectos, FichaCongelacion, sprites,
       getEnemigo(actualzacion.enemyID)));
    break;
    case Communication::TargetPower::Type::ray:
    agregarEfectos(FichaEfectos(idEfectos, FichaRayos, sprites,
       getEnemigo(actualzacion.enemyID)));
    break;
  }
}
void OrdenadorDeFichas::agregarPing(int x, int y){
  idEfectos++;
  agregarEfectos(FichaEfectos(x, y, idEfectos, FichaPing, sprites));
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


#define largo 88
void OrdenadorDeFichas::cargarMapa(std::string &mapa){
  Map mapaCargado;
  auto aux = YAML::Load(mapa);
  mapaCargado.loadFromNode(aux);
  int tematica;
  switch (mapaCargado.getSetting()) {
    case Map::Setting::desert:
      tematica = FichaPisoFondoDesierto;
      break;
    case Map::Setting::volcano:
      tematica = FichaPisoFondoLava;
      break;
    case Map::Setting::ice:
      tematica = FichaPisoFondoGelido;
      break;
    case Map::Setting::meadow:
      tematica = FichaPisoFondoPradera;
      break;
  }
  int x = mapaCargado.getHeight();
  int y = mapaCargado.getWidth();
  int id = 0;

  for (int i = 1; i < x; i++) {
    for (int j = 1; j < y; j++) {
      id++;
      agregarTerreno(FichaTerreno(largo*i-44, largo*j-44, id, tematica, sprites));
    }
  }

  auto pisosFirmes = mapaCargado.getFirmGround();
  for (auto it = pisosFirmes.begin() ; it != pisosFirmes.end(); ++it){
    id = ObetenerTerrenoEnEstaPosicion((it->x)*88-44,(it->y)*88-44);
    getTerreno(id).cambiarTipo(FichaPisoFirme, sprites);
  }

  auto pathEnemigos = mapaCargado.getPaths();
  for (auto it = pathEnemigos.begin() ; it != pathEnemigos.end(); ++it){
    for (auto it2 = it->pathSequence.begin(); it2 != it->pathSequence.end(); ++it2){
      id = ObetenerTerrenoEnEstaPosicion((it2->x)*88-44,(it2->y)*88-44);
      if (id != 0)
        getTerreno(id).cambiarTipo(FichaPisoEnemigos, sprites);
    }
  }
}
