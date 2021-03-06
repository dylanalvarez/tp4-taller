#ifndef __ORDEANADORDEFICHAS_H__
#define __ORDEANADORDEFICHAS_H__

#include <gtkmm.h>
#include <iostream>
#include <list>
#include <mutex>
#include "sprites.h"
#include "Fichas.h"
#include "TiposDeDatosExpeciales.h"
#include "VectorDeSprites.h"
#include "GestionadorDeSonidos.h"


class OrdenadorDeFichas {
private:
    GestionadorDeSonidos sonidos;
    std::vector<std::thread> thread;
    std::mutex m;
    VectorDeSprites sprites; //para creara  las fichas.
    std::map<int, FichaTerreno> terreno;
    std::map<int, FichaTorre> torres;
    std::map<int, FichaEnemigo> enemigos;
    int idEnemigo = 0;
    int idTorre = 0;
    int idEfectos = 0;
    std::map<int, FichaEfectos> poderes;
    std::vector<FichaPortal> portales;
    bool hayFichaGrieta;
    bool hayFichaTornado;
    bool hayFichaVentisca;
    bool hayFichafireWall;

    void imprimirPortal(const Cairo::RefPtr<Cairo::Context> &cr,
                        DatosPantalla datosActuales);

    void imprimirEfectos(const Cairo::RefPtr<Cairo::Context> &cr,
                         DatosPantalla datosActuales);

    void imprimirTorres(const Cairo::RefPtr<Cairo::Context> &cr,
                        DatosPantalla datosActuales);

    void imprimirTerreno(const Cairo::RefPtr<Cairo::Context> &cr,
                         DatosPantalla datosActuales);

    void actualizarEnemigo(Communication::Enemy actualzacion);

    void actualizarTorre(Communication::Tower actualzacion);

    void actualizarEfectos(Communication::PositionalPower actualzacion);

    void actualizarEfectos(Communication::TargetPower actualzacion);

    void actualizarEstadoDeMagias(int tipo);

    void auementarTiempoDeMagias(int tipo);
public:
    void ejecutarCicloDeAnimacion();

    void preprarParaActualizacion();

    void imprir(const Cairo::RefPtr<Cairo::Context> &cr,
                DatosPantalla datosActuales);

    void actualizar(const Communication::GameState &gameState);


    void agregarTerreno(FichaTerreno nuevaFicha);

    int ObetenerTerrenoEnEstaPosicion(int x, int y);

    FichaTerreno &getTerreno(int id);

    void agregarTorre(FichaTorre nuevaFicha);

    int ObetenerTorreEnEstaPosicion(int x, int y);

    FichaTorre &getTorre(int id);

    void agregarEnemigo(FichaEnemigo nuevaFicha);

    void imprimirEnemigo(const Cairo::RefPtr<Cairo::Context> &cr,
                         DatosPantalla datosActuales);

    int ObetenerEnemigoEnEstaPosicion(int x, int y);

    FichaEnemigo &getEnemigo(int id);

    void
    agregarEfectos(int inicio, int objetivo, int id2, VectorDeSprites &sprites);

    void agregarEfectos(FichaEfectos nuevaFicha);

    void agregarPing(int x, int y);

    void agregarPortal(FichaPortal nuevaFicha);

    void cargarMapa(std::string &mapa);

    OrdenadorDeFichas();

    ~OrdenadorDeFichas();
};

#endif
