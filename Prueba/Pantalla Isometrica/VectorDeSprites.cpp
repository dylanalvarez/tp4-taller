#include "VectorDeSprites.h"


VectorDeSprites::VectorDeSprites(){
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/PisoFirme.png"));
  sprites.push_back(Gdk::Pixbuf::create_from_file("Sprites/TorreDeTierra.png"));  
}
Glib::RefPtr<Gdk::Pixbuf>& VectorDeSprites::obtener (int n){
  return (sprites[n]);
}
