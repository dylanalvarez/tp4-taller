#ifndef __FSPRITES_H__
#define __FSPRITES_H__
//cosa a mejorar
#include <gtkmm.h>
#include <iostream>
#include <list>


//FichaSprite Sobre todo me aleja a mi de la logica de imprimir imagenes.
class FichaSprite{
protected:
  Glib::RefPtr<Gdk::Pixbuf> &image; //cosa a mejorar
  int x;
  int y;
public:
  FichaSprite(int x2, int y2, Glib::RefPtr<Gdk::Pixbuf>& image2);
  virtual void dibujarme(const Cairo::RefPtr<Cairo::Context>& cr);
  virtual void dibujarmeIsometrico(const Cairo::RefPtr<Cairo::Context>& cr, int desplasamientoX, int desplasamientoY);
  virtual void pulsaion();
  void cambiarPosicion(int x2, int y2);
  virtual ~FichaSprite();
};
/*
class FichaGift: public FichaSprite{
protected:
  //int id; esto hay que ver.
  Glib::RefPtr<Gdk::Pixbuf> *imageActual;
  Glib::RefPtr<Gdk::Pixbuf> image1;
  Glib::RefPtr<Gdk::Pixbuf> image2;
  //y todas las necesarias.
  std::list<Glib::RefPtr<Gdk::Pixbuf>*> animacion;
  int pulsacionesParaCambio;
  int i;
public:
  //Cosa a pensar mejor
  FichaGift(int x2, int y2);
  //La idea es que cada sprite sea un objetio distinto.
  void dibujarme(const Cairo::RefPtr<Cairo::Context>& cr);
  void pulsaion();
};*/
#endif
