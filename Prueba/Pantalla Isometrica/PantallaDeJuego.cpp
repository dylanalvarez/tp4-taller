#include "PantallaDeJuego.h"
//estos dos van en Pixeles.
#define VelocidadDesplasamiento 5
#define SpriteWidth 79
#define SpriteHeigth 159
//esto es para terminar de ajustar la escala.
#define ConstantenMagicaEscala 5 //cantidad de sprites de largo

bool PantallaDeJuego::on_key_press_event(GdkEventKey* event){
  if (event->keyval == GDK_KEY_w) {
      desplasamientoY += VelocidadDesplasamiento;
  }
  if (event->keyval == GDK_KEY_s) {
      desplasamientoY -= VelocidadDesplasamiento;
  }
  if (event->keyval == GDK_KEY_a) {
      desplasamientoX += VelocidadDesplasamiento;
  }
  if (event->keyval == GDK_KEY_d) {
      desplasamientoX -= VelocidadDesplasamiento;
  }
  queue_draw();
  return Gtk::DrawingArea::on_key_press_event(event);
}

bool PantallaDeJuego::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
  Gtk::Allocation allocation = get_allocation();
  width = allocation.get_width();
  height = allocation.get_height();
// por alguna razon dejo de funcionar.
//  double width2 = (double)width/SpriteWidth/ConstantenMagicaEscala;
//  double height2 = (double)height/SpriteHeigth/ConstantenMagicaEscala;
//  cr->scale(width2,height2);
//  cr->save();

  fichas.imprimirTerreno(cr,desplasamientoX,desplasamientoY);
  fichas.imprimirTorres(cr,desplasamientoX,desplasamientoY);
  return true;
}
PantallaDeJuego::PantallaDeJuego(OrdenadorDeFichas &fichas2): fichas(fichas2){
  set_can_focus(true); //activa la relacion con el teclado
  desplasamientoX = 120;
  desplasamientoY = 120;
}
void PantallaDeJuego::pulsasion(){
  fichas.pulsasion();
  queue_draw(); //Esto redibuja
}
PantallaDeJuego::~PantallaDeJuego(){
}
