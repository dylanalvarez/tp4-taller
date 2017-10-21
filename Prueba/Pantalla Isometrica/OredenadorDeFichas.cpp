#include "OrdenadorDeFichas.h"
#define error 0

void OrdenadorDeFichas::pulsasion(){
  for (auto it = terreno.begin(); it != terreno.end(); ++it){
    it->second.pulsaion();
  }
  for (auto it = torres.begin(); it != torres.end(); ++it){
    it->second.pulsaion();
  }
}

//terreno
void OrdenadorDeFichas::agregarTerreno(FichaTerreno nuevaFicha){
  terreno.emplace(std::make_pair(nuevaFicha.getId(),nuevaFicha));
}
void OrdenadorDeFichas::imprimirTerreno(const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY){
  for (auto it = terreno.begin(); it != terreno.end(); ++it){
    it->second.dibujar(cr,desplasamientoX,desplasamientoY);
  }
}
int OrdenadorDeFichas::ObetenerTerrenoEnEstaPosicion(int x, int y){
  for (auto it = terreno.begin(); it != terreno.end(); ++it){
    if (it->second.colisionaConmigo(x,y)) {
      //it->second.imprimierCordenadas();
      return it->first;
    }
  }
  return error;
}
//torres
void OrdenadorDeFichas::agregarTorre(FichaTorre nuevaFicha){
  torres.emplace(std::make_pair(nuevaFicha.getId(),nuevaFicha));
}
void OrdenadorDeFichas::imprimirTorres(const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY){
  for (auto it = torres.begin(); it != torres.end(); ++it){
    it->second.dibujar(cr,desplasamientoX,desplasamientoY);
  }
}
int OrdenadorDeFichas::ObetenerTorreEnEstaPosicion(int x, int y){
  for (auto it = torres.begin(); it != torres.end(); ++it){
    if (it->second.colisionaConmigo(x,y)) {
      it->second.imprimierCordenadas();
      return it->first;
    }
  }
  return 0;
}

FichaTorre& OrdenadorDeFichas::getTorre(int id){
  return torres.at(id);
}
