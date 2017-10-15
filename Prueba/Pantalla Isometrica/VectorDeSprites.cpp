#include "VectorDeSprites.h"


VectorDeSprites::VectorDeSprites(){
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/PisoFirme.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/TorreDeTierra.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/SueloLava1.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/SueloLava2.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/SueloLava3.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/SueloLava4.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/SueloEnemigo.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/TorreDeFuego.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/TorreFuego1.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/TorreFuego2.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/TorreFuego3.png"));           
}
Glib::RefPtr<Gdk::Pixbuf>& VectorDeSprites::obtener (int n){
  return (sprites[n]);
}
