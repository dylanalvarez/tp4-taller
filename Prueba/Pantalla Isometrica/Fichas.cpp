#include "Fichas.h"
#include <stdlib.h>

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

void Ficha::dibujar(const Cairo::RefPtr<Cairo::Context>& cr, int desplasamientoX, int desplasamientoY){
 sprites[spriteActual].dibujarIsometrico(cr,desplasamientoX,desplasamientoY); //en el futuro pasar x y y
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
Ficha::~Ficha(){
}

bool Ficha::colisionaConmigo(int x2, int y2){
  return ((x-medioLargoX)<x2)&&((x+medioLargoX)>x2)&&
          ((y-medioAltoY)<y2)&&((y+medioAltoY)>y2);
}

//echa para revisar nada mas. Quitar despues.
void Ficha::imprimierCordenadas(){
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
      sprites.push_back(Sprite(x-145, y-145, vectorDeSprites.obtener(SpriteTorreDeAgua)));
      sprites.push_back(Sprite(x-330, y-330, vectorDeSprites.obtener(SpriteAgua1)));
      sprites.push_back(Sprite(x-330, y-330, vectorDeSprites.obtener(SpriteAgua2)));
      sprites.push_back(Sprite(x-330, y-330, vectorDeSprites.obtener(SpriteAgua3)));
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
   int desplasamientoX, int desplasamientoY){
 sprites[spriteActual].dibujarIsometrico(cr,desplasamientoX,desplasamientoY);
 if (tipo != FichaTorreDeTierra) {
   sprites[spriteActualSubAnimacion].dibujarIsometrico(cr,desplasamientoX,desplasamientoY);
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

//FichasEfectos
#define DSP 160 //desplasamientoSpritePortal
#define DSEPY 115 //desplasamientoSpriteEfectoPortal
#define DSEPX 100 //desplasamientoSpriteEfectoPortal
FichaPortal::FichaPortal(int x2, int y2, int id2, int tipo,
                        VectorDeSprites &vectorDeSprites): Ficha(x2, y2, id2, tipo){
  spriteActualSubAnimacion = 1;
  switch (tipo) {
    case FichaPortalAzul:
      y = y - 44;
      sprites.push_back(Sprite(x-DSP, y-DSP, vectorDeSprites.obtener(PortalAzul)));
      sprites.push_back(Sprite(x-DSEPX, y-DSEPY, vectorDeSprites.obtener(PortalAzul1)));
      sprites.push_back(Sprite(x-DSEPX, y-DSEPY, vectorDeSprites.obtener(PortalAzul2)));
      sprites.push_back(Sprite(x-DSEPX, y-DSEPY, vectorDeSprites.obtener(PortalAzul3)));
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
   int desplasamientoX, int desplasamientoY){
    sprites[spriteActualSubAnimacion].dibujarIsometrico(cr,desplasamientoX,desplasamientoY);
    sprites[spriteActual].dibujarIsometrico(cr,desplasamientoX,desplasamientoY);
   }
void FichaPortal::ejecutarSicloDeAnimacion(){
  spriteActualSubAnimacion++;
  if (spriteActualSubAnimacion == 4) {
     spriteActualSubAnimacion = 1;
  }
}
