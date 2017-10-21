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

void Ficha::pulsaion(){
// sprites[spriteActual].pulsaion();
} //Para los gif

void Ficha::cambiarPosicion(int x2, int y2){
  x = x2;
  y = y2;
}

int Ficha::getId(){
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
      sprites.push_back(Sprite(x-67, y-67, vectorDeSprites.obtener(SpriteTorreDeTierra)));
      break;
    case FichaTorreDeFuego:
      sprites.push_back(Sprite(x-110, y-110, vectorDeSprites.obtener(SpriteTorreDeFuego)));
      sprites.push_back(Sprite(x-290, y-290, vectorDeSprites.obtener(SpriteFuego1)));
      sprites.push_back(Sprite(x-290, y-290, vectorDeSprites.obtener(SpriteFuego2)));
      sprites.push_back(Sprite(x-290, y-290, vectorDeSprites.obtener(SpriteFuego3)));
      break;
    default:
    //falta que aca salte un error.
      break;
  }
}

FichaTorre::FichaTorre(const FichaTorre &p): Ficha(p){
  spriteActualSubAnimacion = 1;
}

void FichaTorre::dibujar(const Cairo::RefPtr<Cairo::Context>& cr, int desplasamientoX, int desplasamientoY){
 sprites[spriteActual].dibujarIsometrico(cr,desplasamientoX,desplasamientoY);
 if (tipo != FichaTorreDeTierra) {
   sprites[spriteActualSubAnimacion].dibujarIsometrico(cr,desplasamientoX,desplasamientoY);
 }
}

void FichaTorre::pulsaion(){
  spriteActualSubAnimacion++;
  if (spriteActualSubAnimacion == 4) {
     spriteActualSubAnimacion = 1;
  }
}
