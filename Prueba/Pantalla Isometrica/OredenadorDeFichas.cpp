#include "OrdenadorDeFichas.h"

void OrdenadorDeFichas::imprimirVector(std::vector<Ficha> &vector,
                      const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY){
  for (std::vector<Ficha>::iterator it = vector.begin();
    it != vector.end(); ++it){
    (it)->pulsaion();
    (it)->dibujarme(cr,desplasamientoX,desplasamientoY);
    cr->save();
    }
}

void OrdenadorDeFichas::agregarTerreno(Ficha nuevaFicha){
  terreno.push_back(nuevaFicha);
  //FichasPorId[nuevaFicha.getId()] = &nuevaFicha; Cosa a ver despues
}
void OrdenadorDeFichas::imprimirTerreno(const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY){
  imprimirVector(terreno, cr, desplasamientoX, desplasamientoY);
}

void OrdenadorDeFichas::agregarTorre(Ficha nuevaFicha){
  torres.push_back(nuevaFicha);
  //FichasPorId[nuevaFicha.getId()] = &nuevaFicha; Cosa a ver despues
}
void OrdenadorDeFichas::imprimirTorres(const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY){
  imprimirVector(torres, cr, desplasamientoX, desplasamientoY);
}
