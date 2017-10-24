#include "VectorDeSprites.h"


void VectorDeSprites::cargarSprite(const char* direccion){
  try{ //ver esto.
    sprites.push_back(Gdk::Pixbuf::create_from_file(direccion));
  }
  catch(const Gio::ResourceError& ex){
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  }
  catch(const Gdk::PixbufError& ex){
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }
}
VectorDeSprites::VectorDeSprites(){
  cargarSprite("Sprites/PisoFirme.png");
  cargarSprite("Sprites/TorreDeTierra.png");
  cargarSprite("Sprites/SueloLava1.png");
  cargarSprite("Sprites/SueloLava2.png");
  cargarSprite("Sprites/SueloLava3.png");
  cargarSprite("Sprites/SueloLava4.png");
  cargarSprite("Sprites/SueloEnemigo.png");
  cargarSprite("Sprites/TorreDeFuego.png");
  cargarSprite("Sprites/TorreFuego1.png");
  cargarSprite("Sprites/TorreFuego2.png");
  cargarSprite("Sprites/TorreFuego3.png");
  cargarSprite("Sprites/TorreDeAgua.png");
  cargarSprite("Sprites/TorreAgua1.png");
  cargarSprite("Sprites/TorreAgua2.png");
  cargarSprite("Sprites/TorreAgua3.png");
  cargarSprite("Sprites/TorreDeAire.png");
  cargarSprite("Sprites/TorreAire1.png");
  cargarSprite("Sprites/TorreAire2.png");
  cargarSprite("Sprites/TorreAire3.png");
  cargarSprite("Sprites/PortalAzul.png");
  cargarSprite("Sprites/PortalAzul1.png");
  cargarSprite("Sprites/PortalAzul2.png");
  cargarSprite("Sprites/PortalAzul3.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante1.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante2.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante3.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante4.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante5.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante6.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante7.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante8.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante9.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante10.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante11.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante12.png");
}
Glib::RefPtr<Gdk::Pixbuf>& VectorDeSprites::obtener (int n){
  return (sprites[n]);
}
