#include "PantallaDeJuego.h"
//estos dos van en Pixeles.
#define VelocidadDesplasamiento 5
#define SpriteWidth 79
#define SpriteHeigth 159
//esto es para terminar de ajustar la escala.
#define ConstantenMagicaEscala 5 //cantidad de sprites de largo
#define NoColicion 0
#define AreaDeDesplasamiento 100
// o son cosntante o se calculan al crear la pantalla de juego
#define desplasamientoSuperiorX 1000
#define desplasamientoInferiorX 500
#define desplasamientoSuperiorY 400
#define desplasamientoInferiorY 500

void PantallaDeJuego::desplasamientoIncirementeEnX(){
  if((desplasamientoX + VelocidadDesplasamiento) < desplasamientoSuperiorX)
    desplasamientoX += VelocidadDesplasamiento;
}
void PantallaDeJuego::desplasamientoDecrementoEnX(){
  if((desplasamientoX - VelocidadDesplasamiento) > -desplasamientoInferiorX)
    desplasamientoX -= VelocidadDesplasamiento;
}
void PantallaDeJuego::desplasamientoIncirementeEnY(){
  if((desplasamientoY + VelocidadDesplasamiento) < desplasamientoSuperiorY)
    desplasamientoY += VelocidadDesplasamiento;
}
void PantallaDeJuego::desplasamientoDecrementoEnY(){
  if((desplasamientoY - VelocidadDesplasamiento) > -desplasamientoInferiorY)
    desplasamientoY -= VelocidadDesplasamiento;
}

bool PantallaDeJuego::on_leave_notify_event(GdkEventCrossing* event){
  incirementeEnX = false;
  decrementoEnX = false;
  incirementeEnY = false;
  decrementoEnY = false;
  return Gtk::DrawingArea::on_leave_notify_event(event);
}
bool PantallaDeJuego::on_key_press_event(GdkEventKey* event){
  if (event->keyval == GDK_KEY_w)
      desplasamientoIncirementeEnY();
  if (event->keyval == GDK_KEY_s)
      desplasamientoDecrementoEnY();
  if (event->keyval == GDK_KEY_a)
      desplasamientoIncirementeEnX();
  if (event->keyval == GDK_KEY_d)
      desplasamientoDecrementoEnX();
  queue_draw();
  return Gtk::DrawingArea::on_key_press_event(event);
}
bool PantallaDeJuego::on_motion_notify_event(GdkEventMotion* event){
  incirementeEnX = false;
  decrementoEnX = false;
  incirementeEnY = false;
  decrementoEnY = false;

  if (event->x < AreaDeDesplasamiento)
      incirementeEnX = true;
  if (event->x > width -AreaDeDesplasamiento)
      decrementoEnX = true;
  if (event->y < AreaDeDesplasamiento)
      incirementeEnY = true;
  if (event->y > height -AreaDeDesplasamiento)
      decrementoEnY = true;
  queue_draw();
  return Gtk::DrawingArea::on_motion_notify_event(event);
}
bool PantallaDeJuego::ejecutarSicloDeAnimacion(){
  fichas.ejecutarSicloDeAnimacion(); //trabajar en esto para reducir la cantidad de pulsos.
  queue_draw(); //Esto redibuja
  return true;
}
bool PantallaDeJuego::ejecutarSicloDesplasamientos(){
  if (incirementeEnX)
      desplasamientoIncirementeEnX();
  if (decrementoEnX)
      desplasamientoDecrementoEnX();
  if (incirementeEnY)
      desplasamientoIncirementeEnY();
  if (decrementoEnY)
      desplasamientoDecrementoEnY();
  queue_draw(); //Esto redibuja
  return true;
}
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
  if (id != NoColicion)
    menuTorres.cargarTorre(fichas.getTorre(id));
  else
    menuTorres.decelecionarTorre ();
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
  fichas.imprimirPortal(cr,desplasamientoX,desplasamientoY);
  return true; //esto es parte del formato de timer..
}

PantallaDeJuego::PantallaDeJuego(OrdenadorDeFichas &fichas2,
                            	Glib::RefPtr<Gtk::Builder> &ventana):
                            fichas(fichas2), menuTorres(ventana){
  set_can_focus(true); //activa la relacion con el teclado
  add_events(Gdk::BUTTON_PRESS_MASK);
  add_events(Gdk::LEAVE_NOTIFY_MASK);
  add_events(Gdk::POINTER_MOTION_MASK); //activa las otras relaciones
  desplasamientoX = 120;
  desplasamientoY = 120;
  menuTorres.decelecionarTorre();	
}
PantallaDeJuego::~PantallaDeJuego(){
}
