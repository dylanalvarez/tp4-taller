#include "OrdenadorDeFichas.h"

/*void OrdenadorDeFichas::imprimirVector(std::vector<Ficha> &vector,
                      const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY){
  for (std::vector<Ficha>::iterator it = vector.begin();
    it != vector.end(); ++it){
//    (it)->pulsaion();
    (it)->dibujarme(cr,desplasamientoX,desplasamientoY);
    cr->save();
    }
}*/

void OrdenadorDeFichas::pulsasion(){
  for (std::vector<Ficha>::iterator it = terreno.begin();
        it != terreno.end(); ++it){
    (it)->pulsaion();
  }
  for (std::vector<FichaTorre>::iterator it = torres.begin();
    it != torres.end(); ++it){
    (it)->pulsaion();
  }
}

void OrdenadorDeFichas::agregarTerreno(Ficha nuevaFicha){
  terreno.push_back(nuevaFicha);
  //FichasPorId[nuevaFicha.getId()] = &nuevaFicha; Cosa a ver despues
}
void OrdenadorDeFichas::imprimirTerreno(const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY){
  for (std::vector<Ficha>::iterator it = terreno.begin();
    it != terreno.end(); ++it){
    (it)->dibujarme(cr,desplasamientoX,desplasamientoY);
    cr->save();
  }
}

void OrdenadorDeFichas::agregarTorre(FichaTorre nuevaFicha){
  torres.push_back(nuevaFicha);
  //FichasPorId[nuevaFicha.getId()] = &nuevaFicha; Cosa a ver despues
}
void OrdenadorDeFichas::imprimirTorres(const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY){
  for (std::vector<FichaTorre>::iterator it = torres.begin();
    it != torres.end(); ++it){
    //(it)->pulsaion();
    (it)->dibujarme(cr,desplasamientoX,desplasamientoY);
    cr->save();
  }
}
