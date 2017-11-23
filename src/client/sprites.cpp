#include "sprites.h"
//estos dos van en Pixeles.
#define SpriteWidth 79
#define SpriteHeigth 159
#define ConstantenEscala 15
#define ConstantenIsometricaX 0.897727272
#define ConstantenIsometricaY 0.443181818
#define LimiteDeDibujoX 100
#define LimiteDeDibujoY 200

Sprite::Sprite(int x2, int y2, Glib::RefPtr<Gdk::Pixbuf>& image2)
            : image (image2), x(x2), y(y2){
}

void Sprite::dibujar(const Cairo::RefPtr<Cairo::Context>& cr){
  Gdk::Cairo::set_source_pixbuf(cr, image, x,y);
	cr->rectangle(x, y, x + image->get_width(), y + image->get_height()); //esto es importante.
	cr->fill();
	cr->restore();
  cr->save();
}

void Sprite::dibujarIsometrico(const Cairo::RefPtr<Cairo::Context>& cr,
                                      DatosPantalla datosActuales){
  int x2, y2;
  //lo pongo isometrico
  x2 = (ConstantenIsometricaX)*(x-y); //79/88
  y2 = (ConstantenIsometricaY)*(x+y); //39/88
  //lo desplaso por la pantalla.
  x2 = x2 + datosActuales.desplasamientoX;
  y2 = y2 + datosActuales.desplasamientoY;

  if (x2 < (0-LimiteDeDibujoX) || x2 > (datosActuales.width+LimiteDeDibujoX) ||
        y2 < (0-LimiteDeDibujoY) || y2 > (datosActuales.height+LimiteDeDibujoY))
    return;

  int correctorX = image->get_width()/2, correctorY = image->get_height()/2;
  //esto "carga" la imagen
  Gdk::Cairo::set_source_pixbuf(cr, image, x2- correctorX,y2- correctorY);
  //esto dice que parte de la imagen se muetra.
	cr->rectangle(x2 - correctorX, y2 - correctorY,
    x2 + image->get_width() + correctorX, y2 + image->get_height() + correctorY);
  //y estos dos ni idea.. pero son necesarios.
	cr->fill();
	cr->restore();
  cr->save();
}


void Sprite::cambiarPosicion(int x2, int y2){
  x = x2;
  y = y2;
}

Sprite::~Sprite(){
}

int Sprite::obtenerAlto(){
  return image->get_height();
}

int Sprite::obtenerHancho(){
  return image->get_width();
}
