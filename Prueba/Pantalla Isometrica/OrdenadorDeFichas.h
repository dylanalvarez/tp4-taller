#ifndef __ORDEANADORDEFICHAS_H__
#define __ORDEANADORDEFICHAS_H__

#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <map>
#include "sprites.h"
#include "Fichas.h"


class OrdenadorDeFichas{
private:
 std::map<int,FichaTerreno> terreno;
 std::map<int,FichaTorre> torres;
 std::map<int,Ficha> enemigos;
 std::map<int,Ficha> poderes;
 std::vector<FichaPortal> portales;
protected:
public:
 void ejecutarSicloDeAnimacion();
 
 void agregarTerreno(FichaTerreno nuevaFicha);
 void imprimirTerreno(const Cairo::RefPtr<Cairo::Context>& cr,
                      int desplasamientoX, int desplasamientoY);
 int ObetenerTerrenoEnEstaPosicion(int x, int y);

 void agregarTorre(FichaTorre nuevaFicha);
 void imprimirTorres(const Cairo::RefPtr<Cairo::Context>& cr,
                       int desplasamientoX, int desplasamientoY);
 int ObetenerTorreEnEstaPosicion(int x, int y);
 FichaTorre& getTorre(int id);

 void agregarPortal(FichaPortal nuevaFicha);
 void imprimirPortal(const Cairo::RefPtr<Cairo::Context>& cr,
                       int desplasamientoX, int desplasamientoY);
};
#endif
