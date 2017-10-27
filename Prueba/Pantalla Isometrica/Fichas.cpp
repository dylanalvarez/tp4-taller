#include "Fichas.h"
#include <stdlib.h>

//esta funcion puede ser mejorada a futuro.
Ficha::Ficha(){
}
Ficha::Ficha(int x2, int y2, int id2, int tipo2): x(x2), y(y2), id(id2), tipo(tipo2){
 spriteActual = 0;
 medioLargoX = 44;
 medioAltoY = 44;
}
Ficha::Ficha(const Ficha &p): Ficha(p.x, p.y, p.id, p.tipo){
  for (auto it = p.sprites.begin();it != p.sprites.end(); ++it){
    sprites.push_back(*it);
  }
}
void Ficha::dibujar(const Cairo::RefPtr<Cairo::Context>& cr, DatosPantalla datosActuales){
 sprites[spriteActual].dibujarIsometrico(cr, datosActuales); //en el futuro pasar x y y
}
void Ficha::ejecutarSicloDeAnimacion(){
 // sprites[spriteActual].pulsaion();
} //Para los gif
void Ficha::cambiarPosicion(int x2, int y2){
  x = x2;
  y = y2;
}
int Ficha::getId() const{
  return id;
}
int Ficha::getTipo() const{
  return tipo;
}
Posicion Ficha::getPosicio() const{
  Posicion retorno;
  retorno.X = x;
  retorno.Y = y;
  return retorno;
}
Ficha::~Ficha(){
}
bool Ficha::colisionaConmigo(int x2, int y2){
  return ((x-medioLargoX)<x2)&&((x+medioLargoX)>x2)&&
          ((y-medioAltoY)<y2)&&((y+medioAltoY)>y2);
}

//echa para revisar nada mas. Quitar despues.
void Ficha::imprimierCordenadas() const{
  printf("x: %i, y: %i\n", x, y);
}

//fichasTerreno
FichaTerreno::FichaTerreno(int x2, int y2, int id2, int tipo,
                        VectorDeSprites &vectorDeSprites): Ficha(x2, y2, id2, tipo){
  int random;
  switch (tipo) {
    case FichaPisoFirme:
      sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(SpritePisoFirme)));
      break;
    case FichaPisoEnemigos:
      sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(SpriteSueloEnemigo)));
      break;
    case FichaPisoFondoLava:
      random = rand() % 3;
      sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(SpriteSueloLava1 + random)));
      /*los suelos de lava van son en verdad int de 2 a 5.
      Por lo que el random te hace de ir de uno a ottros
      La otra opcion es un switch dentro de un switch*/
      break;
    default:
    //falta que aca salte un error.
      break;
  }
}
FichaTerreno::FichaTerreno(const FichaTerreno &p): Ficha(p){
}
void FichaTerreno::cambiarTipo(int tipo){
}

//FichaTorre
FichaTorre::FichaTorre(int x2, int y2, int id2, int tipo,
                        VectorDeSprites &vectorDeSprites): Ficha(x2, y2, id2, tipo){
  spriteActualSubAnimacion = 1;
  switch (tipo) {
    case FichaTorreDeTierra:
      danio = 20;
      rango = 2;
      especial = 0;
      sprites.push_back(Sprite(x-67, y-67, vectorDeSprites.obtener(SpriteTorreDeTierra)));
      break;
    case FichaTorreDeFuego:
      danio = 6;
      rango = 3;
      especial = 1;
      sprites.push_back(Sprite(x-110, y-110, vectorDeSprites.obtener(SpriteTorreDeFuego)));
      sprites.push_back(Sprite(x-290, y-290, vectorDeSprites.obtener(SpriteFuego1)));
      sprites.push_back(Sprite(x-290, y-290, vectorDeSprites.obtener(SpriteFuego2)));
      sprites.push_back(Sprite(x-290, y-290, vectorDeSprites.obtener(SpriteFuego3)));
      break;
    case FichaTorreDeAgua:
      danio = 4;
      rango = 3;
      especial = 25; //%
      sprites.push_back(Sprite(x-52, y-52, vectorDeSprites.obtener(SpriteTorreDeAgua)));
      sprites.push_back(Sprite(x-120, y-120, vectorDeSprites.obtener(SpriteAgua1)));
      sprites.push_back(Sprite(x-120, y-120, vectorDeSprites.obtener(SpriteAgua2)));
      sprites.push_back(Sprite(x-120, y-120, vectorDeSprites.obtener(SpriteAgua3)));
      break;
    case FichaTorreDeAire:
      danio = 2;
      rango = 5;
      especial = 10; //Daño contra areo.
      sprites.push_back(Sprite(x-110, y-110, vectorDeSprites.obtener(SpriteTorreDeAire)));
      sprites.push_back(Sprite(x-290, y-290, vectorDeSprites.obtener(SpriteAire1)));
      sprites.push_back(Sprite(x-290, y-290, vectorDeSprites.obtener(SpriteAire2)));
      sprites.push_back(Sprite(x-290, y-290, vectorDeSprites.obtener(SpriteAire3)));
      break;
    default:
    //falta que aca salte un error.
      break;
  }
}
FichaTorre::FichaTorre(const FichaTorre &p): Ficha(p){
  spriteActualSubAnimacion = p.spriteActualSubAnimacion;
  danio = p.danio;
  rango = p.rango;
  especial = p.especial;
}
void FichaTorre::dibujar(const Cairo::RefPtr<Cairo::Context>& cr,
   DatosPantalla datosActuales){
 sprites[spriteActual].dibujarIsometrico(cr,datosActuales);
 if (tipo != FichaTorreDeTierra) {
   sprites[spriteActualSubAnimacion].dibujarIsometrico(cr,datosActuales);
 }
}
void FichaTorre::ejecutarSicloDeAnimacion(){
  spriteActualSubAnimacion++;
  if (spriteActualSubAnimacion == 4) {
     spriteActualSubAnimacion = 1;
  }
}
int FichaTorre::getDanio() const{
  return danio;
}
int FichaTorre::getRango() const{
  return rango;
}
int FichaTorre::getEspecial() const{
  return especial;
}

//FichasEnemigos
FichaEnemigo::FichaEnemigo(int x2, int y2, int id2, int tipo,
                        VectorDeSprites &vectorDeSprites): Ficha(x2, y2, id2, tipo){
  inicioAnimiacionActual = 0;
  int i;
  correccionX = 0;
  correccionY = 0;
  switch (tipo) {
    case Abmonible:
      for (i = 0; i < SpriteAbominableTotal; i++) {
          sprites.push_back(Sprite(x, y, vectorDeSprites.obtener(SpriteAbominableInicial + i)));
      }
      medioLargoX = sprites[0].obtenerAlto()/2;
      medioAltoY = sprites[0].obtenerHancho()/2;
      break;
    default:
    //falta que aca salte un error.
      break;
  }
}
//aunque esto puede que no tenga razon de ser.
FichaEnemigo::FichaEnemigo(const FichaEnemigo &p): Ficha(p){
  inicioAnimiacionActual = p.inicioAnimiacionActual;
}
void FichaEnemigo::dibujar(const Cairo::RefPtr<Cairo::Context>& cr,
   DatosPantalla datosActuales){
    sprites[inicioAnimiacionActual + spriteActual].cambiarPosicion(x,y);
    sprites[inicioAnimiacionActual + spriteActual].dibujarIsometrico(cr,datosActuales);
  }
void FichaEnemigo::ejecutarSicloDeAnimacion(){
  spriteActual++;
  if (spriteActual == 11) {
     spriteActual = 0;
  }
}


//FichasEfectos
#define DSP 160 //desplasamientoSpritePortal
#define DSEPY 115 //desplasamientoSpriteEfectoPortal
#define DSEPX 100 //desplasamientoSpriteEfectoPortal
FichaPortal::FichaPortal(int x2, int y2, int id2, int tipo,
                        VectorDeSprites &vectorDeSprites):
                         Ficha(x2, y2, id2, tipo){
  spriteActualSubAnimacion = 1;
  switch (tipo) {
    case FichaPortalAzul:
      y = y - 44;
      sprites.push_back(Sprite(x-DSP, y-DSP, vectorDeSprites.obtener(SpritePortalAzul)));
      sprites.push_back(Sprite(x-DSEPX, y-DSEPY, vectorDeSprites.obtener(SpritePortalAzul1)));
      sprites.push_back(Sprite(x-DSEPX, y-DSEPY, vectorDeSprites.obtener(SpritePortalAzul2)));
      sprites.push_back(Sprite(x-DSEPX, y-DSEPY, vectorDeSprites.obtener(SpritePortalAzul3)));
      break;
    default:
    //falta que aca salte un error.
      break;
  }
}
//aunque esto puede que no tenga razon de ser.
FichaPortal::FichaPortal(const FichaPortal &p): Ficha(p){
  spriteActualSubAnimacion = p.spriteActualSubAnimacion;
}
void FichaPortal::dibujar(const Cairo::RefPtr<Cairo::Context>& cr,
   DatosPantalla datosActuales){
    sprites[spriteActualSubAnimacion].dibujarIsometrico(cr,datosActuales);
    sprites[spriteActual].dibujarIsometrico(cr,datosActuales);
   }
void FichaPortal::ejecutarSicloDeAnimacion(){
  spriteActualSubAnimacion++;
  if (spriteActualSubAnimacion == 4) {
     spriteActualSubAnimacion = 1;
  }
}


//FichaEfectos
FichaEfectos::FichaEfectos(FichaTorre &inicio, int id2,
   VectorDeSprites &sprites, FichaEnemigo &objetivo2): objetivo(&objetivo2){
  spriteActual = 0;
  medioLargoX = 0;
  medioAltoY = 0;
  id = id2;
  destrulleme = false;
  Posicion posicionInicial;
  posicionInicial = inicio.getPosicio();
  x = posicionInicial.X;
  y = posicionInicial.Y;
  tipo = inicio.getTipo();
  this->sprites.push_back(Sprite(x, y, sprites.obtener(SpriteFuego1)));
  tiempoImpacto = 20;
}

FichaEfectos::FichaEfectos(const FichaEfectos &p): Ficha(p){
  tiempoImpacto = p.tiempoImpacto;
  objetivo = p.objetivo;
  destrulleme = p.destrulleme;
}

bool FichaEfectos::siguesVivo() const{
  return destrulleme;
}

void FichaEfectos::ejecutarSicloDeAnimacion(){
 if (tiempoImpacto == 0) {
   destrulleme = true;
   return;
 }
 Posicion posicionFinal;
 posicionFinal = objetivo->getPosicio();
 int x2 = posicionFinal.X;
 int y2 = posicionFinal.Y;
 x = x - (x-x2)/tiempoImpacto;
 y = y - (y-y2)/tiempoImpacto;
 tiempoImpacto--;
}

void FichaEfectos::dibujar(const Cairo::RefPtr<Cairo::Context>& cr,
  DatosPantalla datosActuales){
   sprites[spriteActual].cambiarPosicion(x,y);
   sprites[spriteActual].dibujarIsometrico(cr,datosActuales);
 }
