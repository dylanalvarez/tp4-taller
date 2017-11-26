#include "Fichas.h"

//esta funcion puede ser mejorada a futuro.
Ficha::Ficha() {}

Ficha::Ficha(int x2, int y2, int id2, int tipo2) : x(x2), y(y2), id(id2),
                                                   tipo(tipo2) {
    spriteActual = 0;
    medioLargoX = 44;
    medioAltoY = 44;
}

Ficha::Ficha(const Ficha &p) : Ficha(p.x, p.y, p.id, p.tipo) {
    for (auto it = p.sprites.begin(); it != p.sprites.end(); ++it) {
        sprites.push_back(*it);
    }
}

void Ficha::dibujar(const Cairo::RefPtr<Cairo::Context> &cr,
                    DatosPantalla datosActuales) {
    sprites[spriteActual].dibujarIsometrico(cr,
                                            datosActuales); //en el futuro pasar x y y
}

void Ficha::ejecutarCicloDeAnimacion() {
    // sprites[spriteActual].pulsaion();
} //Para los gif
void Ficha::cambiarPosicion(int x2, int y2) {
    x = x2;
    y = y2;
}

int Ficha::getId() const {
    return id;
}

int Ficha::getTipo() const {
    return tipo;
}

Posicion Ficha::getPosicion() const {
    Posicion retorno;
    retorno.X = x;
    retorno.Y = y;
    return retorno;
}

Ficha::~Ficha() {}

bool Ficha::colisionaConmigo(int x2, int y2) {
    return ((x - medioLargoX) <= x2) && ((x + medioLargoX) >= x2) &&
           ((y - medioAltoY) <= y2) && ((y + medioAltoY) >= y2);
}

//echa para revisar nada mas.
void Ficha::imprimierCordenadas() const {
    printf("x: %i, y: %i\n", x, y);
}

bool Ficha::deboSerDestruido() const {
    return destrulleme;
}

void Ficha::setDestrulleme(bool valor) {
    destrulleme = valor;
}

//fichasTerreno
FichaTerreno::FichaTerreno(int x2, int y2, int id2, int tipo,
                           VectorDeSprites &vectorDeSprites) : Ficha(x2, y2,
                                                                     id2,
                                                                     tipo) {
    int random;
    switch (tipo) {
        case FichaPisoFirme:
            sprites.push_back(
                    Sprite(x, y, vectorDeSprites.obtener(SpritePisoFirme)));
            break;
        case FichaPisoEnemigos:
            sprites.push_back(
                    Sprite(x, y, vectorDeSprites.obtener(SpriteSueloEnemigo)));
            break;
        case FichaPisoFondoLava:
            random = rand() % 3;
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                    SpriteSueloLava1 + random)));
            /*los suelos de lava van son en verdad int de 2 a 5.
            Por lo que el random te hace de ir de uno a ottros
            La otra opcion es un switch dentro de un switch*/
            break;
        case FichaPisoFondoPradera:
            random = rand() % 3;
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                    SpritePradera1 + random)));
            break;
        case FichaPisoFondoGelido:
            random = rand() % 3;
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                    SpriteSueloGelido1 + random)));
            break;
        case FichaPisoFondoDesierto:
            random = rand() % 3;
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                    SpriteDecierto1 + random)));
            break;
        default:
            //falta que aca salte un error.
            break;
    }
}

FichaTerreno::FichaTerreno(const FichaTerreno &p) : Ficha(p) {}

void FichaTerreno::cambiarTipo(int tipo, VectorDeSprites &vectorDeSprites) {
    sprites.clear();
    this->tipo = tipo;
    int random;
    switch (tipo) {
        case FichaPisoFirme:
            sprites.push_back(
                    Sprite(x, y, vectorDeSprites.obtener(SpritePisoFirme)));
            break;
        case FichaPisoEnemigos:
            sprites.push_back(
                    Sprite(x, y, vectorDeSprites.obtener(SpriteSueloEnemigo)));
            break;
        case FichaPisoFondoLava:
            random = rand() % 3;
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                    SpriteSueloLava1 + random)));
            break;
        case FichaPisoFondoPradera:
            random = rand() % 3;
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                    SpritePradera1 + random)));
            break;
        case FichaPisoFondoGelido:
            random = rand() % 3;
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                    SpriteSueloGelido1 + random)));
            break;
        case FichaPisoFondoDesierto:
            random = rand() % 3;
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                    SpriteDecierto1 + random)));
            break;
        default:
            //falta que aca salte un error.
            break;
    }
}

//FichaTorre
#define CPTT 42 //correccion Posicion Torre Tierra
#define CPTF 42 //correccion Posicion Torre Fuego
#define CPEF 112 //correccion Posicion Efecto Fuego
#define CPTW 52 //correccion Posicion Torre Agua
#define CPEW 120 //correccion Posicion Efecto Agua
#define CPTA 42 //correccion Posicion Torre Aire
#define CPEA 120 //correccion Posicion Efecto Aire

FichaTorre::FichaTorre(int x2, int y2, int id2, int tipo,
                       VectorDeSprites &vectorDeSprites) : Ficha(x2, y2, id2,
                                                                 tipo) {
    spriteActualSubAnimacion = 1;
    switch (tipo) {
        case FichaTorreDeTierra:
            danio = 20;
            rango = 2;
            especial = 0;
            sprites.push_back(Sprite(x - CPTT, y - CPTT,
                                     vectorDeSprites.obtener(
                                             SpriteTorreDeTierra)));
            break;
        case FichaTorreDeFuego:
            danio = 6;
            rango = 3;
            especial = 1;
            sprites.push_back(Sprite(x - CPTF, y - CPTF,
                                     vectorDeSprites.obtener(
                                             SpriteTorreDeFuego)));
            sprites.push_back(Sprite(x - CPEF, y - CPEF,
                                     vectorDeSprites.obtener(SpriteFuego1)));
            sprites.push_back(Sprite(x - CPEF, y - CPEF,
                                     vectorDeSprites.obtener(SpriteFuego2)));
            sprites.push_back(Sprite(x - CPEF, y - CPEF,
                                     vectorDeSprites.obtener(SpriteFuego3)));
            break;
        case FichaTorreDeAgua:
            danio = 4;
            rango = 3;
            especial = 25; //% (cambiar por tiempo)
            sprites.push_back(Sprite(x - CPTW, y - CPTW,
                                     vectorDeSprites.obtener(
                                             SpriteTorreDeAgua)));
            sprites.push_back(Sprite(x - CPEW, y - CPEW,
                                     vectorDeSprites.obtener(SpriteAgua1)));
            sprites.push_back(Sprite(x - CPEW, y - CPEW,
                                     vectorDeSprites.obtener(SpriteAgua2)));
            sprites.push_back(Sprite(x - CPEW, y - CPEW,
                                     vectorDeSprites.obtener(SpriteAgua3)));
            break;
        case FichaTorreDeAire:
            danio = 2;
            rango = 5;
            especial = 0;
            sprites.push_back(Sprite(x - CPTA, y - CPTA,
                                     vectorDeSprites.obtener(
                                             SpriteTorreDeAire)));
            sprites.push_back(Sprite(x - CPEA, y - CPEA,
                                     vectorDeSprites.obtener(SpriteAire1)));
            sprites.push_back(Sprite(x - CPEA, y - CPEA,
                                     vectorDeSprites.obtener(SpriteAire2)));
            sprites.push_back(Sprite(x - CPEA, y - CPEA,
                                     vectorDeSprites.obtener(SpriteAire3)));
            break;
        default:
            //falta que aca salte un error.
            break;
    }
}

int traducirTipTorre(Communication::Tower::Type tipo) {
    switch (tipo) {
        case Communication::Tower::Type::earth:
            return FichaTorreDeTierra;
        case Communication::Tower::Type::water:
            return FichaTorreDeAgua;
        case Communication::Tower::Type::fire:
            return FichaTorreDeFuego;
        case Communication::Tower::Type::air:
            return FichaTorreDeAire;
    }
    return -1;
}

FichaTorre::FichaTorre(Communication::Tower actualzacion,
                       VectorDeSprites &sprites) : FichaTorre(actualzacion.x,
                                                              actualzacion.y,
                                                              actualzacion.id,
                                                              traducirTipTorre(
                                                                      actualzacion.type),
                                                              sprites) {
}

void FichaTorre::actualizar(Communication::Tower actualzacion) {
    danio = actualzacion.damage.normal;
    rango = actualzacion.rangeInSquares;
    especial = actualzacion.slowdown.percentage + actualzacion.ExplosionRange;
}

FichaTorre::FichaTorre(const FichaTorre &p) : Ficha(p) {
    spriteActualSubAnimacion = p.spriteActualSubAnimacion;
    danio = p.danio;
    rango = p.rango;
    especial = p.especial;
}

void FichaTorre::dibujar(const Cairo::RefPtr<Cairo::Context> &cr,
                         DatosPantalla datosActuales) {
    sprites[spriteActual].dibujarIsometrico(cr, datosActuales);
    if (tipo != FichaTorreDeTierra) {
        sprites[spriteActualSubAnimacion].dibujarIsometrico(cr, datosActuales);
    }
}

void FichaTorre::ejecutarCicloDeAnimacion() {
    spriteActualSubAnimacion++;
    if (spriteActualSubAnimacion == 4) {
        spriteActualSubAnimacion = 1;
    }
}

int FichaTorre::getDanio() const {
    return danio;
}

int FichaTorre::getRango() const {
    return rango;
}

int FichaTorre::getEspecial() const {
    return especial;
}

//FichasEnemigos
FichaEnemigo::FichaEnemigo(int x2, int y2, int id2, int tipo,
                           VectorDeSprites &vectorDeSprites) : Ficha(x2, y2,
                                                                     id2,
                                                                     tipo) {
    inicioAnimiacionActual = 0;
    int i;
    correccionX = 0;
    correccionY = 0;
    switch (tipo) {
        case Abmonible:
            for (i = 0; i < SpriteAbominableTotal; i++) {
                sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                        SpriteAbominableInicial + i)));
            }
            medioLargoX = sprites[0].obtenerAlto() / 2;
            medioAltoY = sprites[0].obtenerHancho() / 2;
            largoAnimiacionActual = ((SpriteAbominableTotal + 1) / 4);
            break;
        case DemonioVerde:
            for (i = 0; i < SpriteDemonioVerdeTotal; i++) {
                sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                        SpriteDemonioVerde + i)));
            }
            medioLargoX = sprites[0].obtenerAlto() / 2;
            medioAltoY = sprites[0].obtenerHancho() / 2;
            largoAnimiacionActual = ((SpriteDemonioVerdeTotal + 1) / 4);
            break;
        case HalconSangriento:
            for (i = 0; i < SpriteAguilaTotal; i++) {
                sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                        SpriteAguila + i)));
            }
            medioLargoX = sprites[0].obtenerAlto() / 2;
            medioAltoY = sprites[0].obtenerHancho() / 2;
            largoAnimiacionActual = ((SpriteAguilaTotal + 1) / 4);
            break;
        case Espectro:
            for (i = 0; i < SpriteEspectroTotal; i++) {
                sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                        SpriteEspectro + i)));
            }
            medioLargoX = sprites[0].obtenerAlto() / 2;
            medioAltoY = sprites[0].obtenerHancho() / 2;
            largoAnimiacionActual = ((SpriteEspectroTotal + 1) / 4);
            break;
        case HombreCabra:
            for (i = 0; i < SpriteCabraTotal; i++) {
                sprites.push_back(
                        Sprite(x, y, vectorDeSprites.obtener(SpriteCabra + i)));
            }
            medioLargoX = sprites[0].obtenerAlto() / 2;
            medioAltoY = sprites[0].obtenerHancho() / 2;
            largoAnimiacionActual = ((SpriteCabraTotal + 1) / 4);
            break;
        case NoMuerto:
            for (i = 0; i < SpriteEsqueletoTotal; i++) {
                sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(
                        SpriteEsqueleto + i)));
            }
            medioLargoX = sprites[0].obtenerAlto() / 2;
            medioAltoY = sprites[0].obtenerHancho() / 2;
            largoAnimiacionActual = ((SpriteEsqueletoTotal + 1) / 4);
            break;
        default:
            //falta que aca salte un error.
            break;
    }
}

int traducirTipEnemigo(Communication::Enemy::Type tipo) {
    switch (tipo) {
        case Communication::Enemy::Type::abmonible:
            return Abmonible;
        case Communication::Enemy::Type::greenDemon:
            return DemonioVerde;
        case Communication::Enemy::Type::goatMan:
            return HombreCabra;
        case Communication::Enemy::Type::undead:
            return NoMuerto;
        case Communication::Enemy::Type::spectre:
            return Espectro;
        case Communication::Enemy::Type::bloodyHawk:
            return HalconSangriento;
    }
    return Abmonible;
}

FichaEnemigo::FichaEnemigo(Communication::Enemy actualzacion,
                           VectorDeSprites &sprites) : FichaEnemigo(
        actualzacion.x, actualzacion.y,
        actualzacion.id, traducirTipEnemigo(actualzacion.type), sprites) {
}

FichaEnemigo::FichaEnemigo(const FichaEnemigo &p) : Ficha(p) {
    inicioAnimiacionActual = p.inicioAnimiacionActual;
    largoAnimiacionActual = p.largoAnimiacionActual;
}

void FichaEnemigo::dibujar(const Cairo::RefPtr<Cairo::Context> &cr,
                           DatosPantalla datosActuales) {
    sprites[inicioAnimiacionActual + spriteActual].cambiarPosicion(x, y);
    sprites[inicioAnimiacionActual + spriteActual].dibujarIsometrico(cr,
                                                                     datosActuales);
}

void FichaEnemigo::ejecutarCicloDeAnimacion() {
    spriteActual++;
    if (spriteActual == largoAnimiacionActual - 1) {
        spriteActual = 0;
    }
}

void FichaEnemigo::actualizar(Communication::Enemy actualzacion) {
    if (x < actualzacion.x)
        inicioAnimiacionActual = largoAnimiacionActual * masX;
    if (x > actualzacion.x)
        inicioAnimiacionActual = largoAnimiacionActual * menosX;
    if (y < actualzacion.y)
        inicioAnimiacionActual = largoAnimiacionActual * masY;
    if (y > actualzacion.y)
        inicioAnimiacionActual = largoAnimiacionActual * menosY;
    x = actualzacion.x;
    y = actualzacion.y;
    destrulleme = false;
}


//FichasEfectos
#define DSP 160 //desplasamientoSpritePortal
#define DSEPY 115 //desplasamientoSpriteEfectoPortal
#define DSEPX 100 //desplasamientoSpriteEfectoPortal

FichaPortal::FichaPortal(int x2, int y2, int id2, int tipo,
                         VectorDeSprites &vectorDeSprites) :
        Ficha(x2, y2, id2, tipo) {
    spriteActualSubAnimacion = 1;
    int largo = 0;
    int inicio = 0;
    switch (tipo) {
        case FichaPortalAzul1:
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(arco01)));
            largo = SpritePortalAzul01Total;
            inicio = SpritePortalAzul01;
            break;
        case FichaPortalRojo1:
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(arco01)));
            largo = SpritePortaRojo01Total;
            inicio = SpritePortaRojo01;
            break;
        case FichaPortalAzul2:
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(arco02)));
            largo = SpritePortalAzul02Total;
            inicio = SpritePortalAzul02;
            break;
        case FichaPortalRojo2:
            sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(arco02)));
            largo = SpritePortaRojo02Total;
            inicio = SpritePortaRojo02;
            break;
        default:
            //falta que aca salte un error.
            break;
    }
    for (int i = 0; i < largo; i++) {
        sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(inicio + i)));
    }
    largoAnimiacionActual = largo;
}

//aunque esto puede que no tenga razon de ser.
FichaPortal::FichaPortal(const FichaPortal &p) : Ficha(p) {
    spriteActualSubAnimacion = p.spriteActualSubAnimacion;
}

void FichaPortal::dibujar(const Cairo::RefPtr<Cairo::Context> &cr,
                          DatosPantalla datosActuales) {
    sprites[spriteActualSubAnimacion].dibujarIsometrico(cr, datosActuales);
    sprites[0].dibujarIsometrico(cr, datosActuales);
}

void FichaPortal::ejecutarCicloDeAnimacion() {
    spriteActualSubAnimacion++;
    if (spriteActualSubAnimacion == 10) {
        spriteActualSubAnimacion = 1;
    }
}


//FichaEfectos
FichaEfectos::FichaEfectos(FichaTorre &inicio, int id2,
                           VectorDeSprites &sprites, FichaEnemigo &objetivo2)
        : objetivo(&objetivo2) {
    spriteActual = 0;
    medioLargoX = 0;
    medioAltoY = 0;
    id = id2;
    destrulleme = false;
    Posicion posicionInicial;
    posicionInicial = inicio.getPosicion();
    int inicioSprites;
    int largo;
    tipo = inicio.getTipo();
    switch (tipo) {
        case FichaTorreDeTierra:
            x = posicionInicial.X - 100;
            y = posicionInicial.Y - 100;
            inicioSprites = SpriteAtaqueTierra;
            largo = SpriteAtaqueTierraTotal;
            break;
        case FichaTorreDeFuego:
            x = posicionInicial.X - 100;
            y = posicionInicial.Y - 100;
            inicioSprites = SpriteAtaqueFuego;
            largo = SpriteAtaqueFuegoTotal;
            break;
        case FichaTorreDeAire:
            x = posicionInicial.X - 100;
            y = posicionInicial.Y - 100;
            inicioSprites = SpriteAtaqueAire;
            largo = SpriteAtaqueAireTotal;
            break;
        case FichaTorreDeAgua:
            x = posicionInicial.X - 100;
            y = posicionInicial.Y - 100;
            inicioSprites = SpriteAtaqueAgua;
            largo = SpriteAtaqueAguaTotal;
            break;
        default:
            x = posicionInicial.X - 100;
            y = posicionInicial.Y - 100;
            inicioSprites = SpriteAtaqueTierra;
            largo = SpriteAtaqueTierraTotal;
            break;
    }
    for (int i = 0; i < largo; i++) {
        this->sprites.push_back(
                Sprite(x, y, sprites.obtener(inicioSprites + i)));
    }
    largoAnimiacionActual = largo;
    tiempoImpacto = largo;
}

FichaEfectos::FichaEfectos(int x2, int y2, int id2, int tipo,
                           VectorDeSprites &sprites) :
        Ficha(x2, y2, id2, tipo) {
    objetivo = NULL;
    destrulleme = false;
    int i;
    switch (tipo) {
        case FichaGrieta:
            for (i = 0; i < SpriteGrietaTotal; i++) {
                this->sprites.push_back(
                        Sprite(x, y, sprites.obtener(SpriteGrieta + i)));
            }
            largoAnimiacionActual = SpriteGrietaTotal;
            tiempoImpacto = SpriteGrietaTotal;
            break;
        case FichafireWall:
            for (i = 0; i < SpriteMdeFuegoTotal; i++) {
                this->sprites.push_back(Sprite(x - 60, y - 60, sprites.obtener(
                        SpriteMdeFuego + i)));
            }
            largoAnimiacionActual = SpriteMdeFuegoTotal;
            tiempoImpacto = SpriteMdeFuegoTotal;
            break;
        case FichaTornado:
            for (i = 0; i < SpriteTornadoTotal; i++) {
                this->sprites.push_back(Sprite(x - 100, y - 100,
                                               sprites.obtener(
                                                       SpriteTornado + i)));
            }
            largoAnimiacionActual = SpriteTornadoTotal;
            tiempoImpacto = SpriteTornadoTotal;
            break;
        case FichaPing:
            for (i = 0; i < 10; i++) {
                this->sprites.push_back(
                        Sprite(x - 100, y - 100, sprites.obtener(SpritePing)));
            }
            largoAnimiacionActual = 10;
            tiempoImpacto = 10;
            break;
        default:
            for (i = 0; i < SpriteGrietaTotal; i++) {
                this->sprites.push_back(
                        Sprite(x, y, sprites.obtener(SpriteGrieta + i)));
            }
            largoAnimiacionActual = SpriteGrietaTotal;
            tiempoImpacto = SpriteGrietaTotal;
            break;
    }
}

FichaEfectos::FichaEfectos(int id2, int tipo, VectorDeSprites &sprites,
                           FichaEnemigo &objetivo2) : objetivo(&objetivo2) {
    spriteActual = 0;
    medioLargoX = 0;
    medioAltoY = 0;
    id = id2;
    destrulleme = false;
    Posicion posicionInicial;
    posicionInicial = objetivo->getPosicion();
    this->tipo = tipo;
    int i;
    switch (tipo) {
        case FichaCongelacion:
            x = posicionInicial.X;
            y = posicionInicial.Y;
            this->sprites.push_back(
                    Sprite(x, y, sprites.obtener(SpriteFuego1)));
            tiempoImpacto = 20;
            break;
        case FichaMetorito:
            printf("hola, falla el sprite del metorito");
            for (i = 0; i < SpriteMetorio2Total; i++) {
                this->sprites.push_back(
                        Sprite(x, y, sprites.obtener(SpriteMetorio2 + i)));
            }
            largoAnimiacionActual = SpriteMetorio2Total;
            tiempoImpacto = SpriteMetorio2Total;
            break;
        case FichaRayos:
            x = posicionInicial.X;
            y = posicionInicial.Y;
        case FichaTornado:
            for (i = 0; i < SpriteRalloTotal; i++) {
                this->sprites.push_back(
                        Sprite(x, y, sprites.obtener(SpriteRallo + i)));
            }
            largoAnimiacionActual = SpriteRalloTotal;
            tiempoImpacto = SpriteRalloTotal;
            break;
            break;
        default:
            break;
    }
}

FichaEfectos::FichaEfectos(const FichaEfectos &p) : Ficha(p) {
    tiempoImpacto = p.tiempoImpacto;
    objetivo = p.objetivo;
    destrulleme = p.destrulleme;
    largoAnimiacionActual = p.destrulleme;

}

void FichaEfectos::ejecutarCicloDeAnimacion() {
    spriteActual++;
    if (spriteActual == largoAnimiacionActual - 1) {
        spriteActual = 0;
    }
}

void FichaEfectos::ejecutarcicloDeActualizacion() {
    if (tiempoImpacto == 0) {
        destrulleme = true;
        return;
    }
    int x2;
    int y2;
    if (tipo < 6) {
        Posicion posicionFinal;
        posicionFinal = objetivo->getPosicion();
        x2 = posicionFinal.X;
        y2 = posicionFinal.Y;
        x = x - (x - x2) / tiempoImpacto;
        y = y - (y - y2) / tiempoImpacto;
        if (objetivo->deboSerDestruido())
            destrulleme = true;
        //si el objetivo se va a destruir en el siguiente ciclo. tambien esto
    }
    tiempoImpacto--;
}

void FichaEfectos::dibujar(const Cairo::RefPtr<Cairo::Context> &cr,
                           DatosPantalla datosActuales) {
    if (tipo < 6) {
        sprites[spriteActual].cambiarPosicion(x, y);
    }
    sprites[spriteActual].dibujarIsometrico(cr, datosActuales);
}
