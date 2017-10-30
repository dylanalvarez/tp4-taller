#include "PantallaDeJuego.h"
//estos dos van en Pixeles.
#define VelocidadDesplasamiento 5
#define SpriteWidth 79
#define SpriteHeigth 159
//esto es para terminar de ajustar la escala.
#define ConstantenMagicaEscala 5 //cantidad de sprites de largo
#define AreaDeDesplasamiento 100
// o son cosntante o se calculan al crear la pantalla de juego
#define desplasamientoSuperiorX 1000
#define desplasamientoInferiorX 500
#define desplasamientoSuperiorY 400
#define desplasamientoInferiorY 500

void PantallaDeJuego::desplasamientoIncirementeEnX(){
  if((datosActuales.desplasamientoX + VelocidadDesplasamiento) < desplasamientoSuperiorX)
    datosActuales.desplasamientoX += VelocidadDesplasamiento;
}
void PantallaDeJuego::desplasamientoDecrementoEnX(){
  if((datosActuales.desplasamientoX - VelocidadDesplasamiento) > -desplasamientoInferiorX)
    datosActuales.desplasamientoX -= VelocidadDesplasamiento;
}
void PantallaDeJuego::desplasamientoIncirementeEnY(){
  if((datosActuales.desplasamientoY + VelocidadDesplasamiento) < desplasamientoSuperiorY)
    datosActuales.desplasamientoY += VelocidadDesplasamiento;
}
void PantallaDeJuego::desplasamientoDecrementoEnY(){
  if((datosActuales.desplasamientoY - VelocidadDesplasamiento) > -desplasamientoInferiorY)
    datosActuales.desplasamientoY -= VelocidadDesplasamiento;
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
  return Gtk::DrawingArea::on_key_press_event(event);
}
bool PantallaDeJuego::on_motion_notify_event(GdkEventMotion* event){
  incirementeEnX = false;
  decrementoEnX = false;
  incirementeEnY = false;
  decrementoEnY = false;

  if (event->x < AreaDeDesplasamiento)
      incirementeEnX = true;
  if (event->x > datosActuales.width -AreaDeDesplasamiento)
      decrementoEnX = true;
  if (event->y < AreaDeDesplasamiento)
      incirementeEnY = true;
  if (event->y > datosActuales.height -AreaDeDesplasamiento)
      decrementoEnY = true;
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
  return true;
}
bool PantallaDeJuego::on_button_press_event(GdkEventButton* event){
  //si es necesario mejorar presision
  int x = event->x;
  int y = event->y;
  x = x - datosActuales.desplasamientoX;
  y = y - datosActuales.desplasamientoY;
  int x2 = (x+y*(2.025641025))/(1.795454544);
  int y2 = (x-y*(2.025641025))/(-1.795454544);

  if (menuTorres.estamosCasteando()){
    menuTorres.lanzarHechizo(fichas.ObetenerTerrenoEnEstaPosicion(x2,y2), //corregir esto.
                              fichas.ObetenerEnemigoEnEstaPosicion(x2,y2));
    return Gtk::DrawingArea::on_button_press_event(event);
  }

  int id = fichas.ObetenerTorreEnEstaPosicion(x2,y2);
  if (id != NoColicion){
    menuTorres.selecionarTorre(fichas.getTorre(id));
    return Gtk::DrawingArea::on_button_press_event(event);
  }
  id = fichas.ObetenerTerrenoEnEstaPosicion(x2,y2);
  if (id != NoColicion){
    menuTorres.selecionarTerreno(fichas.getTerreno(id));
    return Gtk::DrawingArea::on_button_press_event(event);
  }
  menuTorres.decelecionar();
  return Gtk::DrawingArea::on_button_press_event(event);
}
bool PantallaDeJuego::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
  Gtk::Allocation allocation = get_allocation();
  datosActuales.width = allocation.get_width();
  datosActuales.height = allocation.get_height();
// por alguna razon dejo de funcionar.
//  double width2 = (double)width/SpriteWidth/ConstantenMagicaEscala;
//  double height2 = (double)height/SpriteHeigth/ConstantenMagicaEscala;
//  cr->scale(width2,height2);
//  cr->save();

  fichas.imprimirTerreno(cr,datosActuales);
  fichas.imprimirPortal(cr,datosActuales);
  fichas.imprimirEnemigo(cr,datosActuales);
  fichas.imprimirTorres(cr,datosActuales);
  fichas.imprimirEfectos(cr,datosActuales);
  return true; //esto es parte del formato de timer..
}

PantallaDeJuego::PantallaDeJuego(OrdenadorDeFichas &fichas2,
                            	Glib::RefPtr<Gtk::Builder> &ventana):
                            fichas(fichas2), menuTorres(ventana){
  set_can_focus(true); //activa la relacion con el teclado
  add_events(Gdk::BUTTON_PRESS_MASK);
  add_events(Gdk::LEAVE_NOTIFY_MASK);
  add_events(Gdk::POINTER_MOTION_MASK); //activa las otras relaciones
  datosActuales.desplasamientoX = 120;
  datosActuales.desplasamientoY = 120;
}
PantallaDeJuego::~PantallaDeJuego(){
}
void PantallaDeJuego::agregarElemento(Elementos elemento){
  menuTorres.agregarElemento(elemento);
  elementos.push_back(elemento);
}
