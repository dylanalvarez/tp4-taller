#ifndef __ORDEANADORDEFICHAS_H__
#define __ORDEANADORDEFICHAS_H__

#include <gtkmm.h>
#include <iostream>
#include "sprites.h"
#include "Fichas.h"


class OrdenadorDeFichas{
private:
 std::map<int,FichaTerreno> terreno;
 std::map<int,FichaTorre> torres;
 std::map<int,Ficha> enemigos;
 std::map<int,Ficha> poderes;
protected:
public:
 void pulsasion();
 void agregarTerreno(FichaTerreno nuevaFicha);
 void imprimirTerreno(const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY);
  //esto deberia pedir una funcion y aplicarla a toda la lista. Pero la verdad no da el tiempo
 void agregarTorre(FichaTorre nuevaFicha);
 void imprimirTorres(const Cairo::RefPtr<Cairo::Context>& cr,
                       int desplasamientoX, int desplasamientoY);
 int ObetenerTerrenoEnEstaPosicion(int x, int y);
 int ObetenerTorreEnEstaPosicion(int x, int y);
 FichaTorre& getTorre(int id);
};
#endif
