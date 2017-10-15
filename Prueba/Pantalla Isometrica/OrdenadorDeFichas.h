#ifndef __ORDEANADORDEFICHAS_H__
#define __ORDEANADORDEFICHAS_H__

#include <gtkmm.h>
#include <iostream>
#include "sprites.h"
#include "Fichas.h"


class OrdenadorDeFichas{
private:
 std::vector<Ficha> terreno;
 std::vector<FichaTorre> torres;
 std::vector<Ficha> enemigos;
 std::vector<Ficha> poderes;
 std::map<int, Ficha*> FichasPorId;
protected:
public:
 void pulsasion();
 void agregarTerreno(Ficha nuevaFicha);
 void imprimirTerreno(const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY);
  //esto deberia pedir una funcion y aplicarla a toda la lista. Pero la verdad no da el tiempo
 void agregarTorre(FichaTorre nuevaFicha);
 void imprimirTorres(const Cairo::RefPtr<Cairo::Context>& cr,
                       int desplasamientoX, int desplasamientoY);
};
#endif
