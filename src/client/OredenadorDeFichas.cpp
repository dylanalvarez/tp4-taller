#include "OrdenadorDeFichas.h"
#include "../editor/Map.h"
#include <fstream>
#include <iostream>
#include <fstream>
#include "../common/Sound.h"
#include <thread>

#define error 0

void OrdenadorDeFichas::ejecutarCicloDeAnimacion(){
  std::unique_lock<std::mutex> lck(m);
  for (auto it = terreno.begin(); it != terreno.end(); ++it){
    it->second.ejecutarCicloDeAnimacion();
  }
  for (auto it = torres.begin(); it != torres.end(); ++it){
    it->second.ejecutarCicloDeAnimacion();
  }
  for (auto it = enemigos.cbegin(); it != enemigos.cend();) {
    if (it->second.siguesVivo()) { enemigos.erase(it++);
      sonidos.siguienteSonido(SonidoMatarMonstruo);
    } else { ++it; }
  }
  for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
    it->second.ejecutarCicloDeAnimacion();
  }
  for (auto it = poderes.cbegin(); it != poderes.cend();) {
    if (it->second.siguesVivo()) { poderes.erase(it++); } else { ++it; }
  }
  for (auto it = poderes.begin(); it != poderes.end(); ++it){
    it->second.ejecutarCicloDeAnimacion();
  }
  for (auto it = portales.begin(); it != portales.end(); ++it){
    it->ejecutarCicloDeAnimacion();
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
      it->second.ejecutarcicloDeActualizacion();
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
  if(actualzacion.is_attacking){
    auto it = enemigos.find(actualzacion.current_target_id);
    if (it != enemigos.end()){
      sonidos.siguienteSonido(SonidoNuevoAtaque);
      agregarEfectos(actualzacion.id, actualzacion.current_target_id, idEfectos, sprites);
      idEfectos++;
    }
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
  return error;
}
FichaEnemigo& OrdenadorDeFichas::getEnemigo(int id){
  return enemigos.at(id);
}
void OrdenadorDeFichas::actualizarEnemigo(Communication::Enemy actualzacion){
  if (idEnemigo < actualzacion.id) {
    sonidos.siguienteSonido(SonidoNuevoMonstruo);
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

  terreno.clear();
  torres.clear();
  enemigos.clear();
  poderes.clear();
  portales.clear();
  idEnemigo = 0;
  idTorre = 0;
  idEfectos = 0;

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
  for (int i = 1; i <= y; i++) {
    for (int j = 1; j <= x; j++) {
      id++;
      agregarTerreno(FichaTerreno(largo*i-44, largo*j-44, id, tematica, sprites));
    }
  }

  auto pisosFirmes = mapaCargado.getFirmGround();
  for (auto it = pisosFirmes.begin() ; it != pisosFirmes.end(); ++it){
    id = ObetenerTerrenoEnEstaPosicion((it->x)*88-44,(it->y)*88-44);
    if (id != 0) {
      getTerreno(id).cambiarTipo(FichaPisoFirme, sprites);
    }
  }

  auto pathEnemigos = mapaCargado.getPaths();
  for (auto &pathEnemigo : pathEnemigos) {

    //??
    y = mapaCargado.getHeight();
    x = mapaCargado.getWidth();
    //??

    if (pathEnemigo.entry.x==0)
      agregarPortal(FichaPortal(-44,(pathEnemigo.entry.y-1)*largo,1, FichaPortalAzul2 ,sprites));
    if (pathEnemigo.entry.x==x+1) //testear
      agregarPortal(FichaPortal((pathEnemigo.exit.x-1)*largo+44,(pathEnemigo.entry.y-1)*largo,1, FichaPortalAzul2 ,sprites));
    if (pathEnemigo.entry.y==0)
      agregarPortal(FichaPortal((pathEnemigo.entry.x-1)*largo,-44,1, FichaPortalAzul1 ,sprites));
    if (pathEnemigo.entry.y==y+1) //testear
      agregarPortal(FichaPortal((pathEnemigo.entry.x-1)*largo,(pathEnemigo.entry.y-1)*largo-44,1, FichaPortalAzul1 ,sprites));

    if (pathEnemigo.exit.x==0)
      agregarPortal(FichaPortal(-44,(pathEnemigo.exit.y-1)*largo,2, FichaPortalRojo2 ,sprites));
    if (pathEnemigo.exit.x==x+1) //testear
      agregarPortal(FichaPortal((pathEnemigo.exit.x-1)*largo-44,(pathEnemigo.exit.y-1)*largo,1, FichaPortalRojo2 ,sprites));
    if (pathEnemigo.exit.y==0)
      agregarPortal(FichaPortal((pathEnemigo.exit.x-1)*largo,-44,2, FichaPortalRojo1 ,sprites));
    if (pathEnemigo.exit.y==y+1) //testear
      agregarPortal(FichaPortal((pathEnemigo.exit.x-1)*largo,(pathEnemigo.exit.y-1)*largo-44,1, FichaPortalRojo1 ,sprites));



    for (auto it2 = pathEnemigo.pathSequence.begin();
         it2 != pathEnemigo.pathSequence.end(); ++it2){
      if (it2 == pathEnemigo.pathSequence.end() - 1) { return; }
      if (it2->x == (it2 + 1)->x) {
        int start = it2->y < (it2 + 1)->y ? it2->y : (it2 + 1)->y;
        int end = it2->y < (it2 + 1)->y ? (it2 + 1)->y : it2->y;
        for (int yy = start; yy <= end; ++yy) {
          id = ObetenerTerrenoEnEstaPosicion((it2->x) * 88 - 44,
                                             yy * 88 - 44);
          if (id != 0)
            getTerreno(id).cambiarTipo(FichaPisoEnemigos, sprites);
        }
      } else {
        int start = it2->x < (it2 + 1)->x ? it2->x : (it2 + 1)->x;
        int end = it2->x < (it2 + 1)->x ? (it2 + 1)->x : it2->x;
        for (int xx = start; xx <= end; ++xx) {
          id = ObetenerTerrenoEnEstaPosicion(xx * 88 - 44,
                                             (it2->y) * 88 - 44);
          if (id != 0)
            getTerreno(id).cambiarTipo(FichaPisoEnemigos, sprites);
        }
      }
    }
  }

}

OrdenadorDeFichas::OrdenadorDeFichas(){
  thread.push_back(std::thread(&GestionadorDeSonidos::iniciar,std::ref(sonidos)));
  sonidos.siguienteSonido(SonidoMatarMonstruo);
}
OrdenadorDeFichas::~OrdenadorDeFichas(){
  sonidos.terminar();
  for (auto& th : thread) th.join();
}
