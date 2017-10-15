#ifndef __FVECTORSPRITES_H__
#define __FVECTORSPRITES_H__
//cosa a mejorar
#include <gtkmm.h>
#include <iostream>
#include <string>

#define SpritePisoFirme 0
#define SpriteTorreDeTierra 1
#define SpriteSueloLava1 2
#define SpriteSueloLava2 3
#define SpriteSueloLava3 4
#define SpriteSueloLava4 5
#define SpriteSueloEnemigo 6
#define SpriteTorreDeFuego 7
#define SpriteFuego1 8
#define SpriteFuego2 9
#define SpriteFuego3 10


class VectorDeSprites{
protected:
  std::vector<Glib::RefPtr<Gdk::Pixbuf>> sprites;
public:
  VectorDeSprites();
  Glib::RefPtr<Gdk::Pixbuf>& obtener (int n);
};
#endif
