#include "sprites.h"
//estos dos van en Pixeles.
#define SpriteWidth 79
#define SpriteHeigth 159
//esto es para terminar de ajustar la escala.
#define ConstantenMagicaEscala 15 //cantidad de sprites de largo


/*FichaSprite::FichaSprite(int x2, int y2, const char* direccion): x(x2), y (y2){
  image = Gdk::Pixbuf::create_from_file(direccion);
}
FichaSprite::FichaSprite(int x2, int y2): x(x2), y(y2){
  //esto va a ser el "final"
    image = Gdk::Pixbuf::create_from_file("Sprites/PisoFirme.png");
}*/
FichaSprite::FichaSprite(int x2, int y2, Glib::RefPtr<Gdk::Pixbuf>& image2)
            : image (image2), x(x2), y(y2){
}

void FichaSprite::dibujarme(const Cairo::RefPtr<Cairo::Context>& cr){
  Gdk::Cairo::set_source_pixbuf(cr, image, x,y);
	cr->rectangle(x, y, x + image->get_width(), y + image->get_height()); //esto es importante.
	cr->fill();
	cr->restore();
}

void FichaSprite::dibujarmeIsometrico(const Cairo::RefPtr<Cairo::Context>& cr,
                                      int desplasamientoX, int desplasamientoY){
  int x2, y2;
  //lo pongo isometrico
  x2 = (0.897727272)*(x-y); //79/88
  y2 = (0.443181818)*(x+y); //39/88
  //lo desplaso por la pantalla.
  x2 = x2 + desplasamientoX;
  y2 = y2 + desplasamientoY;
  int correctorX = image->get_width()/2, correctorY = image->get_height()/2;
  //esto "carga" la imagen
  Gdk::Cairo::set_source_pixbuf(cr, image, x2- correctorX,y2- correctorY);
  //esto dice que parte de la imagen se muetra.
	cr->rectangle(x2 - correctorX, y2 - correctorY,
    x2 + image->get_width() + correctorX, y2 + image->get_height() + correctorY);
  //y estos dos ni idea.. pero son necesarios.
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

FichaSprite::~FichaSprite(){
}
/*
FichaGift::FichaGift(int x2, int y2): FichaSprite(x2, y2){
  //Cambiar luego por otras
  image1 = Gdk::Pixbuf::create_from_file("Sprites/PisoFirme.png");
  image2 = Gdk::Pixbuf::create_from_file("Rojo.png");
  animacion.push_back(&image1);
  animacion.push_back(&image2);
  imageActual = &image1;
  pulsacionesParaCambio = 2;
  i = 0;
} //La idea es que cada sprite sea un objetio distinto.


void FichaGift::dibujarme(const Cairo::RefPtr<Cairo::Context>& cr){
  Gdk::Cairo::set_source_pixbuf(cr, (*imageActual), x,y);
	cr->rectangle(x, y, x + (*imageActual)->get_width(), y + (*imageActual)->get_height()); //esto es importante.
	cr->fill();
	cr->restore();
}
void FichaGift::pulsaion(){
  i ++;
  if (i == pulsacionesParaCambio) {
    i = 0;
    animacion.push_back(imageActual);
    imageActual = animacion.front();
    animacion.pop_front();
  }
}*/
