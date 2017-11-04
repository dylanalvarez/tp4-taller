#ifndef __ORDEANADORDEFICHAS_H__
#define __ORDEANADORDEFICHAS_H__

#include <gtkmm.h>
#include <iostream>
#include <list>
#include "sprites.h"
#include "Fichas.h"
#include "TiposDeDatosExpeciales.h"
#include "VectorDeSprites.h"

class OrdenadorDeFichas{
private:
 VectorDeSprites sprites; //para creara  las fichas.
 std::map<int,FichaTerreno> terreno;
 std::map<int,FichaTorre> torres;
 std::map<int,FichaEnemigo> enemigos;
 int idEnemigo = 0;
 std::map<int,FichaEfectos> poderes;
 std::vector<FichaPortal> portales;
protected:
public:
 void ejecutarSicloDeAnimacion();
 void preprarParaActualizacion();

 void agregarTerreno(FichaTerreno nuevaFicha);
 void imprimirTerreno(const Cairo::RefPtr<Cairo::Context>& cr,
                      DatosPantalla datosActuales);
 int ObetenerTerrenoEnEstaPosicion(int x, int y);
 FichaTerreno& getTerreno(int id);

 void agregarTorre(FichaTorre nuevaFicha);
 void imprimirTorres(const Cairo::RefPtr<Cairo::Context>& cr,
                       DatosPantalla datosActuales);
 int ObetenerTorreEnEstaPosicion(int x, int y);
 FichaTorre& getTorre(int id);

 void agregarEnemigo(FichaEnemigo nuevaFicha);
 void imprimirEnemigo(const Cairo::RefPtr<Cairo::Context>& cr,
                       DatosPantalla datosActuales);
 int ObetenerEnemigoEnEstaPosicion(int x, int y);
 FichaEnemigo& getEnemigo(int id);
 void actualizarEnemigo(Communication::Enemy actualzacion);

 void agregarEfectos(int inicio, int objetivo, int id2, VectorDeSprites &sprites);
 void agregarEfectos(FichaEfectos nuevaFicha);
 void imprimirEfectos(const Cairo::RefPtr<Cairo::Context>& cr,
                       DatosPantalla datosActuales);

 void agregarPortal(FichaPortal nuevaFicha);
 void imprimirPortal(const Cairo::RefPtr<Cairo::Context>& cr,
                       DatosPantalla datosActuales);
};
#endif
