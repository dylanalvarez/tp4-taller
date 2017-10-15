#include "Fichas.h"
#include <stdlib.h>

Ficha::Ficha(int x2, int y2, int id2): x(x2), y(y2), id(id2){
 spriteActual = 0;
}

void Ficha::dibujarme(const Cairo::RefPtr<Cairo::Context>& cr, int desplasamientoX, int desplasamientoY){
 sprites[spriteActual].dibujarmeIsometrico(cr,desplasamientoX,desplasamientoY); //en el futuro pasar x y y
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

Ficha::~Ficha(){
}

//fichasTerreno
FichaTerreno::FichaTerreno(int x2, int y2, int id2, int tipo,
                        VectorDeSprites &vectorDeSprites): Ficha(x2, y2, id2){
  int random;
  switch (tipo) {
    case FichaPisoFirme:
      sprites.push_back(FichaSprite(x, y, vectorDeSprites.obtener(SpritePisoFirme)));
      break;
    case FichaPisoEnemigos:
      sprites.push_back(FichaSprite(x, y, vectorDeSprites.obtener(SpriteSueloEnemigo)));
      break;
    case FichaPisoFondoLava:
      random = rand() % 3;
      sprites.push_back(FichaSprite(x, y, vectorDeSprites.obtener(SpriteSueloLava1 + random)));
      /*los suelos de lava van son en verdad int de 2 a 5.
      Por lo que el random te hace de ir de uno a ottros
      La otra opcion es un switch dentro de un switch*/
      break;
    default:
    //falta que aca salte un error.
      break;
  }
}

void FichaTerreno::cambiarTipo(int tipo){
}

//FichaTorre
FichaTorre::FichaTorre(int x2, int y2, int id2, int tipo,
                        VectorDeSprites &vectorDeSprites): Ficha(x2, y2, id2){
  this->tipo= tipo;
  spriteActualSubAnimacion = 1;
  switch (tipo) {
    case FichaTorreDeTierra:
      sprites.push_back(FichaSprite(x-67, y-67, vectorDeSprites.obtener(SpriteTorreDeTierra)));
      break;
    case FichaTorreDeFuego:
      sprites.push_back(FichaSprite(x-110, y-110, vectorDeSprites.obtener(SpriteTorreDeFuego)));
      sprites.push_back(FichaSprite(x-290, y-290, vectorDeSprites.obtener(SpriteFuego1)));
      sprites.push_back(FichaSprite(x-290, y-290, vectorDeSprites.obtener(SpriteFuego2)));
      sprites.push_back(FichaSprite(x-290, y-290, vectorDeSprites.obtener(SpriteFuego3)));
      break;
    default:
    //falta que aca salte un error.
      break;
  }
}

void FichaTorre::dibujarme(const Cairo::RefPtr<Cairo::Context>& cr, int desplasamientoX, int desplasamientoY){
 sprites[spriteActual].dibujarmeIsometrico(cr,desplasamientoX,desplasamientoY);
 if (tipo != FichaTorreDeTierra) { 
   sprites[spriteActualSubAnimacion].dibujarmeIsometrico(cr,desplasamientoX,desplasamientoY);
 }
}

void FichaTorre::pulsaion(){
  spriteActualSubAnimacion++;
  if (spriteActualSubAnimacion == 4) {
     spriteActualSubAnimacion = 1;
  }
}
