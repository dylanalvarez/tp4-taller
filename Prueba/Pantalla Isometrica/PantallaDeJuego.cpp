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
#define AreaDeDesplasamiento 100
bool PantallaDeJuego::on_motion_notify_event(GdkEventMotion* event){

  if (event->x < AreaDeDesplasamiento) {
      desplasamientoX += VelocidadDesplasamiento;
  }
  if (event->x > width -AreaDeDesplasamiento) {
      desplasamientoX -= VelocidadDesplasamiento;
  }
  if (event->y < AreaDeDesplasamiento) {
      desplasamientoY += VelocidadDesplasamiento;
  }
  if (event->y > height -AreaDeDesplasamiento) {
      desplasamientoY -= VelocidadDesplasamiento;
  }
  queue_draw();
  return Gtk::DrawingArea::on_motion_notify_event(event);
}
#define NoColicion 0
bool PantallaDeJuego::on_button_press_event(GdkEventButton* event){
  //si es necesario mejorar presision
  int x = event->x;
  int y = event->y;
  x = x - desplasamientoX;
  y = y - desplasamientoY;
  int x2 = (x+y*(2.025641025))/(1.795454544);
  int y2 = (x-y*(2.025641025))/(-1.795454544);

  //fichas.ObetenerTerrenoEnEstaPosicion(x2,y2);
  int id = fichas.ObetenerTorreEnEstaPosicion(x2,y2);
  if (id != NoColicion) {
    menuTorres.cargarTorre(fichas.getTorre(id));
  }
  return Gtk::DrawingArea::on_button_press_event(event);
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
  return true; //esto es parte del formato de timer..
}
PantallaDeJuego::PantallaDeJuego(OrdenadorDeFichas &fichas2,
                            	Glib::RefPtr<Gtk::Builder> &ventana):
                            fichas(fichas2), menuTorres(ventana){
  set_can_focus(true); //activa la relacion con el teclado
  add_events(Gdk::BUTTON_PRESS_MASK);
  add_events(Gdk::POINTER_MOTION_MASK); //activa las otras relaciones
  desplasamientoX = 120;
  desplasamientoY = 120;
}
bool PantallaDeJuego::pulsasion(){
  fichas.pulsasion();
  queue_draw(); //Esto redibuja
  return true;
}
PantallaDeJuego::~PantallaDeJuego(){
}
