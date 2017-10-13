#include "Fichas.h"


Ficha::Ficha(int x2, int y2, int id2): x(x2), y(y2), id(id2){
 spriteActual = 0;
}

void Ficha::dibujarme(const Cairo::RefPtr<Cairo::Context>& cr, int desplasamientoX, int desplasamientoY){
 sprites[spriteActual].dibujarmeIsometrico(cr,desplasamientoX,desplasamientoY); //en el futuro pasar x y y
}

void Ficha::pulsaion(){
 sprites[spriteActual].pulsaion();
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
  sprites.push_back(FichaSprite(x, y, vectorDeSprites.obtener(SpritePisoFirme)));
}

void FichaTerreno::cambiarTipo(int tipo){
}

//FichaTorre
FichaTorre::FichaTorre(int x2, int y2, int id2, int tipo,
                        VectorDeSprites &vectorDeSprites): Ficha(x2, y2, id2){
  sprites.push_back(FichaSprite(x-67, y-67, vectorDeSprites.obtener(SpriteTorreDeTierra)));
}
