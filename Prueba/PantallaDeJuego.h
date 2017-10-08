#ifndef __FPANTALLAJUEGO_H__
#define __FPANTALLAJUEGO_H__
//cosa a mejorar
#include <gtkmm.h>
#include <iostream>

class FichaSprite{
private:
  //int id; esto hay que ver.
  int x;
  int y;
public:
  Glib::RefPtr<Gdk::Pixbuf> image; //cosa a mejorar
  FichaSprite(int x2, int y2, const char* direccion);
  void dibujarme(const Cairo::RefPtr<Cairo::Context>& cr);
  void pulsaion();
  void cambiarPosicion(int x2, int y2);
};

class PantallaDeJuego: public Gtk::DrawingArea{
private:
  //tal vez un mapa no sea lo mejor.
 std::map<int,FichaSprite*> sprites; //Int es el "ID"
 int width;
 int height;
protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override; //la verdad de la milaneza
public:
  PantallaDeJuego();
  int agregar(FichaSprite* sprite, int id);
  void pulsaion();
  virtual ~PantallaDeJuego();
};
#endif
