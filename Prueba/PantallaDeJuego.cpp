#include "PantallaDeJuego.h"
//estos dos van en Pixeles.
#define SpriteWidth 10
#define SpriteHeigth 10
//esto es para terminar de ajustar la escala.
#define ConstantenMagicaEscala 10


FichaSprite::FichaSprite(int x2, int y2, const char* direccion): x(x2), y (y2){
  image = Gdk::Pixbuf::create_from_file(direccion);
}

void FichaSprite::dibujarme(const Cairo::RefPtr<Cairo::Context>& cr){
  Gdk::Cairo::set_source_pixbuf(cr, image, x,y);
	cr->rectangle(x, y, x + image->get_width(), y + image->get_height()); //esto es importante.
	cr->fill();
	cr->restore();
}

void FichaSprite::pulsaion(){
  //por ahora nada.. pero aca puede estar el cambio de sprite para el gif
}

void FichaSprite::cambiarPosicion(int x2, int y2){
  x = x2;
  y = y2;
}

bool PantallaDeJuego::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
  Gtk::Allocation allocation = get_allocation();
  width = allocation.get_width();
  height = allocation.get_height();

  double width2 = (double)width/SpriteWidth/ConstantenMagicaEscala;
  double height2 = (double)height/SpriteHeigth/ConstantenMagicaEscala;
  cr->scale(width2,height2);
  cr->save();

  for (std::map<int, FichaSprite*>::iterator it = sprites.begin();
    it != sprites.end(); ++it){
      it->second->dibujarme(cr);
      }
  return true;
}
PantallaDeJuego::PantallaDeJuego(){
}
int PantallaDeJuego::agregar(FichaSprite* sprite, int id){
  //agregar una logica de identificacion...Pero aun no se si quedarme con el mapa
  sprites[id]=sprite;
  return 0;
}
void PantallaDeJuego::pulsaion(){
  queue_draw(); //Esto redibuja
}
PantallaDeJuego::~PantallaDeJuego(){
}
