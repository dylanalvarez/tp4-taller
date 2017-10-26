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
#define SpriteTorreDeAgua 11
#define SpriteAgua1 12
#define SpriteAgua2 13
#define SpriteAgua3 14
#define SpriteTorreDeAire 15
#define SpriteAire1 16
#define SpriteAire2 17
#define SpriteAire3 18
#define SpritePortalAzul 19
#define SpritePortalAzul1 20
#define SpritePortalAzul2 21
#define SpritePortalAzul3 22

#define SpriteAbominableInicial 23
#define SpriteAbominableTotal 47
 //van a ser 44... cargarlos de a uno ya no tiene sentido.

class VectorDeSprites{
protected:
  std::vector<Glib::RefPtr<Gdk::Pixbuf>> sprites;
  void cargarSprite(const char* direccion);
public:
  VectorDeSprites();
  Glib::RefPtr<Gdk::Pixbuf>& obtener (int n);

};
#endif
