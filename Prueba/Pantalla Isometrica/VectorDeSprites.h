#ifndef __FVECTORSPRITES_H__
#define __FVECTORSPRITES_H__
//cosa a mejorar
#include <gtkmm.h>
#include <iostream>
#include <string>

#define SpritePisoFirme 0
#define SpriteTorreDeTierra 1



class VectorDeSprites{
protected:
  std::vector<Glib::RefPtr<Gdk::Pixbuf>> sprites;
public:
  VectorDeSprites();
  Glib::RefPtr<Gdk::Pixbuf>& obtener (int n);
};
#endif
